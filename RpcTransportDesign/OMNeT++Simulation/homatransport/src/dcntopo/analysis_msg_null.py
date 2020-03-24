import sys

with open(sys.argv[1], "r") as fp: 
    lines = fp.readlines()
    exception_counter = 0
    finished_counter = 0
    might_finished_counter = 0
    unfinished_counter = 0
    finished = {}
    unfinished = {}

    null = []
    for line in lines: 
        data = line.split() 
        if len(data) != 7: 
            continue 
    
        if data[2] == "Null": 
            null.append(data[4])

        try: 
            if int(data[4]) <= 1500: 
                # print(line)
                if data[2] not in finished:
                    finished[data[2]] = 1
        except: 
            exception_counter += 1  
    
    for i in null: 
        if i in finished: 
            finished_counter += 1
        else: 
            unfinished_counter += 1

    print("finished: ", finished_counter)
    print("unfinished: ", unfinished_counter)
    fp.close()
