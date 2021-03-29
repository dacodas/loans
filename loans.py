import json

current = {
    "1-01": (8451, .0641),
    "1-05": (13590, .0721),
    "1-09": (15067, .0684),
    "1-10": (16140, .0631),
    "AA": (3060.98, .0386),
    "AB": (2012.88, .0386),
    "AC": (4168.67, .0466),
    "AD": (1761.80, .0466),
    "AE": (4417.19, .0429),
    "AF": (2254.63, .0429),
    "AG": (4715.48, .0376),
    "AH": (1808.37, .0376)
}

def index(key):
    principal, interest = current[key]
    return principal * interest

interest = 0

for count in range(60):
    mostCostly = max(current.keys(), key=index)

    print(json.dumps({"current": current, "toPay": mostCostly}))

    currentMostCostlyPrincipal, interestRate = current[mostCostly]
    current[mostCostly] = (currentMostCostlyPrincipal - 1500, interestRate)

    thisMonthsAccruedInterest = sum([ ( 1 / 12 ) * interestRate * principal for (name, (principal, interestRate)) in current.items()])
    interest += thisMonthsAccruedInterest
    print(json.dumps({
        "accruedInterest": interest,
        "thisMonthsAccruedInterest": thisMonthsAccruedInterest,
        "total": sum([principal for (name, (principal, interestRate)) in current.items()]),
        "totalNelnet": sum([principal for (name, (principal, interestRate)) in current.items() if name.startswith("1")]),
        "totalNavient": sum([principal for (name, (principal, interestRate)) in current.items() if name.startswith("A")])
    }))

