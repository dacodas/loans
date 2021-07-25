void
examplePrints(void)
{
	std::decimal::decimal32 dfpTest { 0.1df };
	float test { 0.1f };

	printf("0.1 as a binary float: %a\n", test);
	printf("0.1 as a decimal float: %Ha\n", 0.1df);
	printf("Example calculation with decimal32:  %Ha\n",
	       4417.19df * .0429df * 0.0833333df);
	printf("Example calculation with decimal64:  %Da\n",
	       4417.19dd * .0429dd * 0.0833333dd);
	printf("Example calculation with decimal128: %DDa\n",
	       4417.19dl * .0429dl * 0.0833333dl);
	printf("Interest split over days: %DDa\n", 0.0641dl / 365.0dl);
}

void
oldPython(void)
{
	// startingMonth = datetime.datetime(month = 7, day = 1, year = 2021)
	// oneMonth = datetime.timedelta(days = 32)
	//
	// loans = Loans([Loan(*loanArguments) for loanArguments in
	// loanArguments]) runThrough(loans, lambda loans: 1500)
	//
	// loans = Loans([Loan(*loanArguments) for loanArguments in
	// loanArguments]) runThrough(loans, lambda loans:
	// loans.minimumMonthlyPayment())
	//
	// loans = Loans([Loan(*loanArguments) for loanArguments in
	// loanArguments]) # runThrough(loans, lambda loans: max(1000,
	// loans.minimumMonthlyPayment()))
	//
	// loans = Loans([Loan(*loanArguments) for loanArguments in
	// loanArguments]) # runThrough(loans, lambda loans: 1000)
}
