#pragma once
#include <array>

struct ContainerAlgebra
{
    template<typename S1, typename S2, typename S3, typename Operation>
    void for_each3 (S1& s1, S2& s2, S3& s3, Operation op) const
    {
        using std::begin;
        using std::end;

        auto first1 = begin(s1);
        auto last1 = end(s1);
        auto first2 = begin(s2);
        auto first3 = begin(s3);
        for(; first1 != last1;)
            op(*first1++, *first2++, *first3++);
    }

    template<typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename Operation>
    void for_each6 (S1& s1, S2& s2, S3& s3, S4& s4, S5& s5, S6& s6, Operation op) const
    {
        using std::begin;
        using std::end;

        auto first1 = begin(s1);
        auto last1 = end(s1);
        auto first2 = begin(s2);
        auto first3 = begin(s3);
        auto first4 = begin(s4);
        auto first5 = begin(s5);
        auto first6 = begin(s6);
        for (; first1 != last1;)
            op(*first1++, *first2++, *first3++, *first4++, *first5++, *first6++);
    }
};


struct DefaultOperations
{
    template <typename F1 = double, typename F2 = F1>
    struct ScaleSum2
    {
        const F1 alpha1;
        const F2 alpha2;
        ScaleSum2(F1 a1, F2 a2) : alpha1{a1}, alpha2{a2} {}
        template<typename T0, typename T1, typename T2>
        void operator() (T0& t0, const T1& t1, const T2& t2) const
        {
            t0 = alpha1 * t1 + alpha2 * t2;
        }
    };
    template <typename F1 = double, typename F2 = F1, typename F3 = F2, typename F4 = F2, typename F5 = F2>
    struct ScaleSum5
    {
        const F1 alpha1;
        const F2 alpha2;
        const F3 alpha3;
        const F4 alpha4;
        const F5 alpha5;
        ScaleSum5(F1 a1, F2 a2, F3 a3, F4 a4, F5 a5) : alpha1{a1}, alpha2{a2}, alpha3{a3}, alpha4{a4}, alpha5{a5} {}
        template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        void operator() (T0& t0, const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5) const
        {
            t0 = alpha1 * t1 + alpha2 * t2 + alpha3 * t3 + alpha4 * t4 + alpha5 * t5;
        }
    };
};

template <typename StateType>
void Resize(const StateType& in, StateType & out)
{
    using std::size;
    out.resize(size(in));
}

template <typename Scalar, std::size_t n>
void Resize(const std::array<Scalar, n>&, std::array<Scalar, n>&) {}

template <typename StateType,
          typename Scalar = double,
          typename Time= Scalar,
          typename Algebra = ContainerAlgebra,
          typename Operations = DefaultOperations>
class RungeKutta4{
public:
    template <typename System>
    void DoStep(System& system, StateType& x, Time t, Time dt)
    {
        AdjustSize(x);
        const Scalar one = 1;
        const Time dt2 = dt/2, dt3 = dt/3, dt6 = dt/6;

        using ScaleSum2 = typename Operations::template ScaleSum2<Scalar, Time>;
        using ScaleSum5 = typename Operations::template ScaleSum5<Scalar, Time, Time, Time, Time>;

        system(x, k1_, t);
        algebra_.for_each3(x_tmp_, x, k1_, ScaleSum2{one, dt2});
        system(x_tmp_, k2_, t+dt2);
        algebra_.for_each3(x_tmp_, x, k2_, ScaleSum2{one, dt2});
        system(x_tmp_, k3_, t+dt2);
        algebra_.for_each3(x_tmp_, x, k3_, ScaleSum2{one, dt});
        system(x_tmp_, k4_, t+dt);
        algebra_.for_each6(x, x, k1_, k2_, k3_, k4_, ScaleSum5{one, dt6, dt3, dt3, dt6});
    }

private:
    StateType x_tmp_, k1_, k2_, k3_, k4_;
    Algebra algebra_;

    void AdjustSize(const StateType& x)
    {
        Resize(x, x_tmp_);
        Resize(x, k1_);
        Resize(x, k2_);
        Resize(x, k3_);
        Resize(x, k4_);
    }
};