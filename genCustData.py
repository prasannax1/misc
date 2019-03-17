def getWords():
    filename = '/home/ubuntu/words'
    with open(filename) as f:
        s = f.readlines()

    return s

from random import randint
def namer(s):
    while True:
        idx = randint(0,len(s)-1)
        yield s[idx].rstrip()

def hash_str(h):
    pre = "{"
    data = ",".join(( ":".join((k, str(v))) for k,v in h.iteritems()))
    return "".join((pre, data))

from random import random
def getItem():
    return "".join((hash_str({
        '"num"': randint(1, 50),
        '"qty"': randint(1, 10),
        '"price"': "{0:.2f}".format(random() * 200)
    }), "}"))

cust_id=1
n = namer(getWords())
def getCust():
    global n
    global cust_id
    pre = hash_str({
        '"cust_id"': cust_id,
        '"last_name"': '"{0}"'.format(next(n)),
        '"first_name"': '"{0}"'.format(next(n))
    })
    it = ', "items":['
    cust_id = cust_id + 1

    no_of_items = randint(1,10)
    items = ",".join((getItem() for i in range(no_of_items)))
    post = "]}"

    return "".join((pre, it, items, post))

total=10000
print "["
for j in range(total):
    print getCust(), ","
print "]"
