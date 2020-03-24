
f = open("bytestotal_blind_GOOGLE_ALL_RPC_2.000000","r")
buckets = []
for i in range(8):
	buckets.append(0)
for line in f:
	lines = line.split(",")
	prio = int(lines[1])
	byte = lines[2].rstrip("\n")
	if prio >= 0 and prio < 8:
		buckets[prio] = buckets[prio] + int(byte)
	else:
		print(prio, " " ,byte)
f.close()
for i in range(len(buckets)):
	print(buckets[i])
