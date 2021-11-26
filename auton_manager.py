FILENAME = "autons.hpp"

def add_to_file(name):
    f = open(FILENAME, "a")
    f.write("\n" + name + "()" + "\n")
    f.write("{\n\t\n}\n")
    f.close()


def change_includes(new_includes):
    remove_to = -1
    
    f = open(FILENAME, "r")
    lines = f.readlines()
    f.close()

    for i in range(len(lines)):
        if lines[i][0:8] == "#include":
            remove_to = i

    f = open(FILENAME, "w")
    for include in new_includes:
        f.write("#include \"" + include + "\"\n")
    f.write("\n")
    
    for i in range(len(lines)):
        if i > remove_to:
            f.write(lines[i])


def split_to_list(list):
    new_list = []
    tempstr = ""
    for char in list:
        if char != ",":
            tempstr += char
        else:
            new_list.append(tempstr)
            tempstr = ""
    if tempstr != "":
        new_list.append(tempstr)
    return new_list


def main():
    choice = input("'a' to add autons.\n'i' to change includes.\n$ ")
    if(choice.lower() == 'a'):
        names = input("Enter autons seperated by commas: ").replace(" ", "")
        new_list = split_to_list(names)
        for item in new_list:
            add_to_file(item)
    elif(choice.lower() == 'i'):
        includes = input("Enter new includes seperated by commas: ").replace(" ", "")
        change_includes(split_to_list(includes))
    else:
        print("no action.")


if __name__ == "__main__":
    main()