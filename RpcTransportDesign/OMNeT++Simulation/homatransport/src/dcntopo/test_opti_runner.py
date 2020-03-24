import d_salt_runner

for aware in [True, False]:
    r = d_salt_runner.Runner('W1', False, n_flows=100_000, timeout= '1.3h', log_prio= True)
    for alpha in [1.0e+2]:
        print(r.run_exp({42: alpha}))
