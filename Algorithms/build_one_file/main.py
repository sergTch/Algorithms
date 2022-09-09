from asyncore import write

main = "Algorithms.cpp"
src = "../"
stl = []
libs = []
done = set()

def get_libs(fname):
    done.add(fname)

    for line in open(src + fname).readlines():
        line = "".join(line.split())
        
        if "#include" == line[:8]:
            if line[8] == '<':
                stl.append(line)
            else:
                lib = line.split('"')[1]
                libs.append(lib)
                
                if lib not in done:
                    get_libs(lib)

get_libs(main)

out_name = "solution.cpp"
out = open(out_name, 'w')

done = set()

for lib in stl[::-1]:
    if lib not in done:
        done.add(lib)
        out.write(lib + '\n')

def add_file(fname):
    print(fname)
    for line in open(src + fname).readlines():
        if "".join(line.split())[:8] != "#include":
            out.write(line)
    out.write("\n")

done = set()

for lib in libs:
    if lib not in done:
        done.add(lib)
        add_file(lib)
        add_file(lib[:-1] + "cpp")

add_file(main)
