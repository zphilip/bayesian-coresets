import numpy as np
import captree as ct
import warnings
import time

class GIGA(object):
  def __init__(self, _x, tree_type='c++'): #options are 'python', 'c++'
    x = np.asarray(_x)
    if len(x.shape) != 2 or not np.issubdtype(x.dtype, np.number):
      raise ValueError('GIGA: input must be a 2d numeric ndarray')
    nrms = np.sqrt((x**2).sum(axis=1))
    self.nzidcs = nrms > 0.
    self.full_N = x.shape[0] #number of vecs (incl zero vecs)
    self.x = x[self.nzidcs, :] #nonzero vectors

    self.norms = nrms[self.nzidcs] #norms of nonzero vecs
    self.sig = self.norms.sum() #norm sum
    self.xs = self.x.sum(axis=0) #sum of nonzero vecs (target vector)
    xsnrm = np.sqrt(((self.xs)**2).sum())
    self.y = self.x/self.norms[:, np.newaxis] #normalized nonzero data
    self.ys = self.xs/(xsnrm if xsnrm > 0. else 1.) #normalized sum vec
    self.N = self.x.shape[0] #number of nonzero vecs
    self.tree = None
    self.tree_type = tree_type
    self.f_preproc = x.shape[0] + 3*self.x.shape[0] + 2
    self.f_lin = 0.
    self.f_update = 0.
    self.f_tree_search_prev = 0.
    self.n_lin = 0
    self.logt_lin = 0.
    self.logtsq_lin = 0.
    self.n_tr = 0
    self.logt_tr = 0.
    self.logtsq_tr = 0.
    self.reached_numeric_limit = False
    self.reset()

  #update_method can be 'fast' or 'accurate'
  #search_method can be 'adaptive', 'linear', or 'tree'
  def run(self, M, update_method='fast', search_method='adaptive'):
    #if M is not greater than self.M, just return 
    if M <= self.M:
      raise ValueError('GIGA.run(): M must be increasing. self.M = '+str(self.M) + ' M = '+str(M))
    if self.x.size == 0 or (self.xs**2).sum() == 0. or self.reached_numeric_limit:
      warnings.warn(
       'GIGA.run(): either data has no nonzero vectors, the sum has norm 0, or the numeric limit has been reached. No more iterations will be run. M = ' + str(self.M) + ', error = ' +str(self.error()))
      return

    if self.y.shape[0] == 1:
      self.yw = self.y[0, :]
      self.wts[0] = 1.
      self.M = 1
      self.reached_numeric_limit = True
      self.f_update += 1.
      return
    if self.y.shape[1] == 1:
      self.yw = self.ys.copy()
      self.wts[np.argmax(self.y.dot(self.ys))] = 1.0
      self.M = 1
      self.reached_numeric_limit = True
      self.f_update += 1.
      return
      
    if search_method == 'linear':
      GIGA.search = GIGA.search_linear
    elif search_method == 'tree':
      GIGA.search = GIGA.search_tree
      if not self.tree:
        self.build_tree()
    else:
      GIGA.search = GIGA.search_adaptive
      if not self.tree:
        self.build_tree()

    #this is commented out since initialization step is exactly the same as the main iteration if y(w) = 0
    #this is true for both tree and linear search
    #if self.M == 0:
    #  scores = self.y.dot(self.ys)
    #  f = scores.argmax()
    #  self.wts[f] = 1.
    #  self.yw = self.y[f, :]
    #  self.M = 1

    for m in range(self.M, M):
      f = self.search()
      gA = -1.
      gB = -1.
      if f >= 0:
        gA = self.ys.dot(self.y[f,:]) - self.ys.dot(self.yw) * self.yw.dot(self.y[f,:])
        gB = self.ys.dot(self.yw) - self.ys.dot(self.y[f,:]) * self.yw.dot(self.y[f,:])
        self.f_update += 3.
   
      #if the direction and/or line search failed
      if gA <= 0. or gB < 0:
        #try recomputing yw from scratch and rerunning search
        self.yw = (self.wts[:, np.newaxis]*self.y).sum(axis=0)
        nrm = np.sqrt((self.yw**2).sum())
        self.yw /= nrm
        self.wts /= nrm
        self.f_update += (self.wts > 0).sum() + 3.

        f = self.search()
        if f >= 0:
          gA = self.ys.dot(self.y[f,:]) - self.ys.dot(self.yw) * self.yw.dot(self.y[f,:])
          gB = self.ys.dot(self.yw) - self.ys.dot(self.y[f,:]) * self.yw.dot(self.y[f,:])
          self.f_update += 3.
        #if it still didn't work, we've reached the numeric limit
        if gA <= 0. or gB < 0:
          self.reached_numeric_limit = True
          break
      #direction+line search worked, update weights + yw
      gamma = gA/(gA+gB)
      self.wts *= (1.-gamma)
      self.wts[f] += gamma

      if update_method == 'fast':
        self.yw = (1.-gamma)*self.yw + gamma*self.y[f, :]
        self.f_update += 1.
      else:
        self.yw = (self.wts[:, np.newaxis]*self.y).sum(axis=0)
        self.f_update += (self.wts > 0).sum()

      nrm = np.sqrt((self.yw**2).sum())
      self.yw /= nrm
      self.wts /= nrm
      self.f_update += 3.
      self.M = m+1

    return

  def search_linear(self):
    t0 = time.clock()

    cdir = self.ys - self.ys.dot(self.yw)*self.yw
    cdirnrm =np.sqrt((cdir**2).sum()) 
    if cdirnrm < 1e-14:
      return -1
    cdir /= cdirnrm
    scorenums = self.y.dot(cdir) 
    scoredenoms = self.y.dot(self.yw)
    #extract points for which the geodesic direction is stable (1st condition) and well defined (2nd)
    idcs = np.logical_and(scoredenoms > -1.+1e-14,  1.-scoredenoms**2 > 0.)
    #compute the norm 
    scoredenoms[idcs] = np.sqrt(1.-scoredenoms[idcs]**2)
    scoredenoms[np.logical_not(idcs)] = np.inf
    #compute the scores
    scores = scorenums/scoredenoms
    amscore = scores.argmax()

    tf = time.clock()
    self.f_lin += 2.*self.N+2.
    self.n_lin += 1
    self.logt_lin += np.log(tf-t0)
    self.logtsq_lin += np.log(tf-t0)**2
    return scores.argmax()
  
  def search_tree(self):

    if not self.tree.is_build_done():
      return self.search_linear() 

    t0 = time.clock()

    cdir = self.ys - self.ys.dot(self.yw)*self.yw
    cdirnrm =np.sqrt((cdir**2).sum()) 
    if cdirnrm < 1e-14:
      return -1
    cdir /= cdirnrm
    nopt = self.tree.search(self.yw, cdir)

    tf = time.clock()
    self.n_tr += 1
    self.logt_tr += np.log(tf-t0)
    self.logtsq_tr += np.log(tf-t0)**2
    return nopt
  
  def search_adaptive(self):
    #this uses UCB1-Normal from Auer et al ``Finite-time Analysis of the Multiarmed Bandit Problem'' (2002)
    n = self.n_tr+self.n_lin + 1
    if self.n_lin < 2 or self.n_lin < np.ceil(8.*np.log(n)):
      return self.search_linear()
    if self.n_tree < 2 or self.n_tree < np.ceil(8.*np.log(n)):
      return self.search_tree()
    lin_idx = self.logt_lin/self.n_lin - np.sqrt(16.*(max(0., self.logtsq_lin - self.logt_lin**2/self.n_lin)/(self.n_lin-1))*(np.log(n-1.)/self.n_lin))
    tree_idx = self.logt_tr/self.n_tr - np.sqrt(16.*(max(0., self.logtsq_tr - self.logt_tr**2/self.n_tr)/(self.n_tr-1))*(np.log(n-1.)/self.n_tr))
    if tree_idx < lin_idx:
      return self.search_tree()
    else:
      return self.search_linear()

  def build_tree(self):
    if self.tree_type == 'python':
      self.tree = ct.CapTree(self.y)
    else:
      self.tree = ct.CapTreeC(self.y)

  def get_num_ops(self):
    ftot = self.f_preproc+self.f_lin + self.f_update
    if self.tree:
      ftot += self.tree.num_build_ops() + self.tree.num_search_ops() - self.f_tree_search_prev
    return ftot

  def reset(self):
    self.M = 0
    self.wts = np.zeros(self.N)
    self.yw = np.zeros(self.y.shape[1])
    self.reached_numeric_limit = False
    if self.tree:
      self.f_tree_search_prev = self.tree.num_search_ops()
    self.f_lin = 0.
    self.f_update = 0

  #options are fast, accurate (either use yw or recompute yw from wts)
  def error(self, method="fast"):
    #if M = 0, just output zeros using the fast method
    if self.M == 0:
      method = "fast"
    if method == "fast":
      return np.sqrt((self.xs**2).sum())*np.sqrt(max(0., 1. - self.yw.dot(self.ys)**2))
    else:
      ywt = (self.wts[:, np.newaxis]*self.y).sum(axis=0)
      ywtn = np.sqrt((ywt**2).sum())
      ywt /= ywtn
      w = ((self.wts/ywtn)/self.norms)*np.sqrt((self.xs**2).sum())*ywt.dot(self.ys)
      return np.sqrt((((w[:, np.newaxis]*self.x).sum(axis=0) - self.xs)**2).sum())

  #options are accurate and fast (either use yw or recompute)
  #by default use accurate computation for weights (since this will be actual output)
  def weights(self, method="accurate"):
    #if M = 0, just output zeros using the fast method
    if self.M == 0:
      method = "fast"
    full_wts = np.zeros(self.full_N)
    if method == "fast":
      full_wts[self.nzidcs] = (self.wts/self.norms)*np.sqrt((self.xs**2).sum())*self.yw.dot(self.ys)
    else:
      ywt = (self.wts[:, np.newaxis]*self.y).sum(axis=0)
      ywtn = np.sqrt((ywt**2).sum())
      ywt /= ywtn
      full_wts[self.nzidcs] = ((self.wts/ywtn)/self.norms)*np.sqrt((self.xs**2).sum())*ywt.dot(self.ys)
    return full_wts

  def exp_bound(self, M=None):
    raise NotImplementedError("GIGA.exp_bound(): not implemented")

  def sqrt_bound(self, M=None):
    raise NotImplementedError("GIGA.sqrt_bound(): not implemented")
    
