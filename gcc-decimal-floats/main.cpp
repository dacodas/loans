#include <decimal/decimal>

#include <fenv.h>
#include <float.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <numeric>


template <typename T>
class Loan {
public:
	std::string identifier;
	T principal;
	T interest;
	T minimumMonthlyPayment;

	T monthlyInterest() const;
	T pay(T amount);
	T payPrincipal(T amount);
};

template <typename T>
class Loans {
private:
	std::vector<Loan<T>> loans;

	static T _minimumMonthlyPaymentAccumulator(T cumulativeSum, const Loan<T>& loan)
	{
		return loan.minimumMonthlyPayment + cumulativeSum;
	}

	static T _principalAccumulator(T cumulativeSum, const Loan<T>& loan)
	{
		return loan.principal + cumulativeSum;
	}

	static T _monthlyInterestAccumulator(T cumulativeSum, const Loan<T>& loan)
	{
		return loan.monthlyInterest() + cumulativeSum;
	}

public:
	using iterator = std::vector<Loan<T>>::iterator;
	using accumulator = T (*)(T, const Loan<T>&);

	Loans<T>(std::vector<Loan<T>> loans) : loans {std::move(loans)} {};

	T minimumMonthlyPayment();
	T principal();
	T monthlyInterest();
	Loan<T>& mostCostlyLoan();
	T pay(T amount);
	void printSummary();
};

#include <Loan.template-functions.include>
#include <Loans.template-functions.include>

template <typename T>
T runThrough(Loans<T> loans, T (*func) (Loans<T>))
{
	T interest {0};

	while ( loans.principal() > 0 )
	{
		interest += loans.monthlyInterest();
		T mmp {loans.minimumMonthlyPayment()};
		
		T payment {func(loans)};
		loans.pay(payment);
		
		loans.printSummary();
	}

	printf("%.100He\n", interest);

	return interest;
}

int main(int argc, char *argv[]) 
{
	std::decimal::decimal32 dfpTest {0.1df};
	float test {0.1f};

	printf("Here is a test: %.100He\n", dfpTest);
	printf("Here is a test: %.100f\n", test);

	Loans<std::decimal::decimal32> loans {{
		{"1-01", 8451.df, .0641df, 215.31df},
		{"1-05", 13590.df, .0721df, 289.35df},
		{"1-09", 15067.df, .0684df, 314.02df},
		{"1-10", 16140.df, .0631df, 254.03df},
		{"AA", 3060.98df, .0386df, 35.97df},
		{"AB", 2012.88df, .0386df, 23.66df},
		{"AC", 4168.67df, .0466df, 57.59df},
		{"AD", 1761.80df, .0466df, 24.34df},
		{"AE", 4417.19df, .0429df, 52.82df},
		{"AF", 2254.63df, .0429df, 26.96df},
		{"AG", 4715.48df, .0376df, 55.19df},
		{"AH", 1808.37df, .0376df, 21.17df},
	}};

	runThrough<std::decimal::decimal32>(loans, [] (Loans<std::decimal::decimal32> loans) -> std::decimal::decimal32 { return 1500.0df; });

	// startingMonth = datetime.datetime(month = 7, day = 1, year = 2021)
	// oneMonth = datetime.timedelta(days = 32)
	// 
	// loans = Loans([Loan(*loanArguments) for loanArguments in loanArguments])
	// runThrough(loans, lambda loans: 1500)
	// 
	// loans = Loans([Loan(*loanArguments) for loanArguments in loanArguments])
	// runThrough(loans, lambda loans: loans.minimumMonthlyPayment())
	// 
	// loans = Loans([Loan(*loanArguments) for loanArguments in loanArguments])
	// # runThrough(loans, lambda loans: max(1000, loans.minimumMonthlyPayment()))
	// 
	// loans = Loans([Loan(*loanArguments) for loanArguments in loanArguments])
	// # runThrough(loans, lambda loans: 1000)

	return 0;
}
