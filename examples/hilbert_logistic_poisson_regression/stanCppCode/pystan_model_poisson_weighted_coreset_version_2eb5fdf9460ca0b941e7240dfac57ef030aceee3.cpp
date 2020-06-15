// Code generated by Stan version 2.19.1
#include <stan/model/model_header.hpp>
#include <iostream>
#include <fstream>
namespace anon_model_c1cf5952f196c3821cdadf0928a94534_namespace {
using std::istream;
using std::string;
using std::stringstream;
using std::cout;
using std::vector;
using stan::io::dump;
using stan::math::lgamma;
using stan::model::prob_grad;
using namespace stan::math;
static int current_statement_begin__;
stan::io::program_reader prog_reader__() {
    stan::io::program_reader reader;
    reader.add_event(0, 0, "start", "unknown file name");
    reader.add_event(22, 20, "end", "unknown file name");
    return reader;
}
class anon_model_c1cf5952f196c3821cdadf0928a94534 : public prob_grad {
private:
        int n;
        int d;
        std::vector<int> y;
        //
        //WEIGHTS MODIFICATION
        std::vector<double> w;
        //
        //
        matrix_d x;
public:
    anon_model_c1cf5952f196c3821cdadf0928a94534(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : prob_grad(0) {
        ctor_body(context__, 0, pstream__);
    }
    anon_model_c1cf5952f196c3821cdadf0928a94534(stan::io::var_context& context__,
        unsigned int random_seed__,
        std::ostream* pstream__ = 0)
        : prob_grad(0) {
        ctor_body(context__, random_seed__, pstream__);
    }
    void ctor_body(stan::io::var_context& context__,
                   unsigned int random_seed__,
                   std::ostream* pstream__) {
        typedef double local_scalar_t__;
        boost::ecuyer1988 base_rng__ =
          stan::services::util::create_rng(random_seed__, 0);
        (void) base_rng__;  // suppress unused var warning
        current_statement_begin__ = -1;
        static const char* function__ = "anon_model_c1cf5952f196c3821cdadf0928a94534_namespace::anon_model_c1cf5952f196c3821cdadf0928a94534";
        (void) function__;  // dummy to suppress unused var warning
        size_t pos__;
        (void) pos__;  // dummy to suppress unused var warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        try {
            // initialize data block variables from context__
            current_statement_begin__ = 3;
            context__.validate_dims("data initialization", "n", "int", context__.to_vec());
            n = int(0);
            vals_i__ = context__.vals_i("n");
            pos__ = 0;
            n = vals_i__[pos__++];
            check_greater_or_equal(function__, "n", n, 0);
            current_statement_begin__ = 4;
            context__.validate_dims("data initialization", "d", "int", context__.to_vec());
            d = int(0);
            vals_i__ = context__.vals_i("d");
            pos__ = 0;
            d = vals_i__[pos__++];
            check_greater_or_equal(function__, "d", d, 0);
            current_statement_begin__ = 5;
            validate_non_negative_index("y", "n", n);
            context__.validate_dims("data initialization", "y", "int", context__.to_vec(n));
            y = std::vector<int>(n, int(0));
            vals_i__ = context__.vals_i("y");
            pos__ = 0;
            size_t y_k_0_max__ = n;
            for (size_t k_0__ = 0; k_0__ < y_k_0_max__; ++k_0__) {
                y[k_0__] = vals_i__[pos__++];
            }
            size_t y_i_0_max__ = n;
            for (size_t i_0__ = 0; i_0__ < y_i_0_max__; ++i_0__) {
                check_greater_or_equal(function__, "y[i_0__]", y[i_0__], 0);
            }
            //
            //WEIGHTS MODIFICATION
            context__.validate_dims("data initialization", "w", "double", context__.to_vec(n));
            w = std::vector<double>(n, int(0));
            vals_r__ = context__.vals_r("w");
            pos__ = 0;
            size_t w_k_0_max__ = n;
            for (size_t k_0__ = 0; k_0__ < w_k_0_max__; ++k_0__) {
                w[k_0__] = vals_r__[pos__++];
            }
            size_t w_i_0_max__ = n;
            for (size_t i_0__ = 0; i_0__ < w_i_0_max__; ++i_0__) {
                check_greater_or_equal(function__, "w[i_0__]", w[i_0__], 0);
            }
            //
            //
            current_statement_begin__ = 6;
            validate_non_negative_index("x", "n", n);
            validate_non_negative_index("x", "d", d);
            context__.validate_dims("data initialization", "x", "matrix_d", context__.to_vec(n,d));
            x = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(n, d);
            vals_r__ = context__.vals_r("x");
            pos__ = 0;
            size_t x_j_2_max__ = d;
            size_t x_j_1_max__ = n;
            for (size_t j_2__ = 0; j_2__ < x_j_2_max__; ++j_2__) {
                for (size_t j_1__ = 0; j_1__ < x_j_1_max__; ++j_1__) {
                    x(j_1__, j_2__) = vals_r__[pos__++];
                }
            }
            // initialize transformed data variables
            // execute transformed data statements
            // validate transformed data
            // validate, set parameter ranges
            num_params_r__ = 0U;
            param_ranges_i__.clear();
            current_statement_begin__ = 9;
            num_params_r__ += 1;
            current_statement_begin__ = 10;
            validate_non_negative_index("theta", "d", d);
            num_params_r__ += d;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    ~anon_model_c1cf5952f196c3821cdadf0928a94534() { }
    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__,
                         std::ostream* pstream__) const {
        typedef double local_scalar_t__;
        stan::io::writer<double> writer__(params_r__, params_i__);
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;
        current_statement_begin__ = 9;
        if (!(context__.contains_r("theta0")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable theta0 missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("theta0");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "theta0", "double", context__.to_vec());
        double theta0(0);
        theta0 = vals_r__[pos__++];
        try {
            writer__.scalar_unconstrain(theta0);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable theta0: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 10;
        if (!(context__.contains_r("theta")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable theta missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("theta");
        pos__ = 0U;
        validate_non_negative_index("theta", "d", d);
        context__.validate_dims("parameter initialization", "theta", "vector_d", context__.to_vec(d));
        Eigen::Matrix<double, Eigen::Dynamic, 1> theta(d);
        size_t theta_j_1_max__ = d;
        for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
            theta(j_1__) = vals_r__[pos__++];
        }
        try {
            writer__.vector_unconstrain(theta);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable theta: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }
    void transform_inits(const stan::io::var_context& context,
                         Eigen::Matrix<double, Eigen::Dynamic, 1>& params_r,
                         std::ostream* pstream__) const {
      std::vector<double> params_r_vec;
      std::vector<int> params_i_vec;
      transform_inits(context, params_i_vec, params_r_vec, pstream__);
      params_r.resize(params_r_vec.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r(i) = params_r_vec[i];
    }
    template <bool propto__, bool jacobian__, typename T__>
    T__ log_prob(std::vector<T__>& params_r__,
                 std::vector<int>& params_i__,
                 std::ostream* pstream__ = 0) const {
        typedef T__ local_scalar_t__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // dummy to suppress unused var warning
        T__ lp__(0.0);
        stan::math::accumulator<T__> lp_accum__;
        try {
            stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
            // model parameters
            current_statement_begin__ = 9;
            local_scalar_t__ theta0;
            (void) theta0;  // dummy to suppress unused var warning
            if (jacobian__)
                theta0 = in__.scalar_constrain(lp__);
            else
                theta0 = in__.scalar_constrain();
            current_statement_begin__ = 10;
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> theta;
            (void) theta;  // dummy to suppress unused var warning
            if (jacobian__)
                theta = in__.vector_constrain(d, lp__);
            else
                theta = in__.vector_constrain(d);
            // transformed parameters
            current_statement_begin__ = 13;
            validate_non_negative_index("f", "n", n);
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> f(n);
            stan::math::initialize(f, DUMMY_VAR__);
            stan::math::fill(f, DUMMY_VAR__);
            // transformed parameters block statements
            current_statement_begin__ = 14;
            stan::math::assign(f, minus(log_inv_logit(minus(add(theta0, multiply(x, theta))))));
            // validate transformed parameters
            const char* function__ = "validate transformed params";
            (void) function__;  // dummy to suppress unused var warning
            current_statement_begin__ = 13;
            size_t f_j_1_max__ = n;
            for (size_t j_1__ = 0; j_1__ < f_j_1_max__; ++j_1__) {
                if (stan::math::is_uninitialized(f(j_1__))) {
                    std::stringstream msg__;
                    msg__ << "Undefined transformed parameter: f" << "(" << j_1__ << ")";
                    stan::lang::rethrow_located(std::runtime_error(std::string("Error initializing variable f: ") + msg__.str()), current_statement_begin__, prog_reader__());
                }
            }
            // model body
            current_statement_begin__ = 17;
            lp_accum__.add(normal_log<propto__>(theta0, 0, 1));
            current_statement_begin__ = 18;
            lp_accum__.add(normal_log<propto__>(theta, 0, 1));
            current_statement_begin__ = 19;
            //
            //WEIGHTS MODIFICATION 
            //we loop over data individually here to give them weights
            //the poisson_log function does not easily allow this when calling using vectors/matrices
            //this is the original code:
            //T__ a = poisson_log<propto__>(y, f);
            //This is the modified code:
            for (size_t j_1__ = 0; j_1__ < f_j_1_max__ ; ++j_1__) {
               lp_accum__.add(w[j_1__]*poisson_log<propto__>(y[j_1__], f(j_1__)));
            }
            //
            //std::cout << "you can place a debugging message using this format, but it will be printed repeatedly because this function is called many times";
            //
            //this is the modified code we tried originally, which does not work:
            //  for (size_t j_1__ = 0; j_1__ < f_j_1_max__; ++j_1__) {
            //     lp_accum__.add(w[j_1__]*poisson_log<propto__>(y[j_1__], f(j_1__)));
            //  }
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
        lp_accum__.add(lp__);
        return lp_accum__.sum();
    } // log_prob()
    template <bool propto, bool jacobian, typename T_>
    T_ log_prob(Eigen::Matrix<T_,Eigen::Dynamic,1>& params_r,
               std::ostream* pstream = 0) const {
      std::vector<T_> vec_params_r;
      vec_params_r.reserve(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        vec_params_r.push_back(params_r(i));
      std::vector<int> vec_params_i;
      return log_prob<propto,jacobian,T_>(vec_params_r, vec_params_i, pstream);
    }
    void get_param_names(std::vector<std::string>& names__) const {
        names__.resize(0);
        names__.push_back("theta0");
        names__.push_back("theta");
        names__.push_back("f");
    }
    void get_dims(std::vector<std::vector<size_t> >& dimss__) const {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(d);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n);
        dimss__.push_back(dims__);
    }
    template <typename RNG>
    void write_array(RNG& base_rng__,
                     std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     bool include_tparams__ = true,
                     bool include_gqs__ = true,
                     std::ostream* pstream__ = 0) const {
        typedef double local_scalar_t__;
        vars__.resize(0);
        stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
        static const char* function__ = "anon_model_c1cf5952f196c3821cdadf0928a94534_namespace::write_array";
        (void) function__;  // dummy to suppress unused var warning
        // read-transform, write parameters
        double theta0 = in__.scalar_constrain();
        vars__.push_back(theta0);
        Eigen::Matrix<double, Eigen::Dynamic, 1> theta = in__.vector_constrain(d);
        size_t theta_j_1_max__ = d;
        for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
            vars__.push_back(theta(j_1__));
        }
        double lp__ = 0.0;
        (void) lp__;  // dummy to suppress unused var warning
        stan::math::accumulator<double> lp_accum__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        if (!include_tparams__ && !include_gqs__) return;
        try {
            // declare and define transformed parameters
            current_statement_begin__ = 13;
            validate_non_negative_index("f", "n", n);
            Eigen::Matrix<double, Eigen::Dynamic, 1> f(n);
            stan::math::initialize(f, DUMMY_VAR__);
            stan::math::fill(f, DUMMY_VAR__);
            // do transformed parameters statements
            current_statement_begin__ = 14;
            stan::math::assign(f, minus(log_inv_logit(minus(add(theta0, multiply(x, theta))))));
            if (!include_gqs__ && !include_tparams__) return;
            // validate transformed parameters
            const char* function__ = "validate transformed params";
            (void) function__;  // dummy to suppress unused var warning
            // write transformed parameters
            if (include_tparams__) {
                size_t f_j_1_max__ = n;
                for (size_t j_1__ = 0; j_1__ < f_j_1_max__; ++j_1__) {
                    vars__.push_back(f(j_1__));
                }
            }
            if (!include_gqs__) return;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    template <typename RNG>
    void write_array(RNG& base_rng,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& vars,
                     bool include_tparams = true,
                     bool include_gqs = true,
                     std::ostream* pstream = 0) const {
      std::vector<double> params_r_vec(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r_vec[i] = params_r(i);
      std::vector<double> vars_vec;
      std::vector<int> params_i_vec;
      write_array(base_rng, params_r_vec, params_i_vec, vars_vec, include_tparams, include_gqs, pstream);
      vars.resize(vars_vec.size());
      for (int i = 0; i < vars.size(); ++i)
        vars(i) = vars_vec[i];
    }
    static std::string model_name() {
        return "anon_model_c1cf5952f196c3821cdadf0928a94534";
    }
    void constrained_param_names(std::vector<std::string>& param_names__,
                                 bool include_tparams__ = true,
                                 bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "theta0";
        param_names__.push_back(param_name_stream__.str());
        size_t theta_j_1_max__ = d;
        for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "theta" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
            size_t f_j_1_max__ = n;
            for (size_t j_1__ = 0; j_1__ < f_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "f" << '.' << j_1__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }
        if (!include_gqs__) return;
    }
    void unconstrained_param_names(std::vector<std::string>& param_names__,
                                   bool include_tparams__ = true,
                                   bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "theta0";
        param_names__.push_back(param_name_stream__.str());
        size_t theta_j_1_max__ = d;
        for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "theta" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
            size_t f_j_1_max__ = n;
            for (size_t j_1__ = 0; j_1__ < f_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "f" << '.' << j_1__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }
        if (!include_gqs__) return;
    }
}; // model
}  // namespace
typedef anon_model_c1cf5952f196c3821cdadf0928a94534_namespace::anon_model_c1cf5952f196c3821cdadf0928a94534 stan_model;
