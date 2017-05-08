f = open('log.csv', 'w')
for i in range (1, 30001):
    f.write(str(i%680)+","+str(i%40+40)+'\n');

f.close()
