import uuid
import os
import os.path
import shutil
import sys

def copy_template(proj_name, path):
    #recursive copying template directory -> path/proj_name
    shutil.copytree("template", os.path.join(path, proj_name))
    #rename files in win direcory (replace T to proj_name)
    win_dir = os.path.join(path, proj_name, "win")
    for filename in os.listdir(win_dir):
        if filename.startswith("T"):
            os.rename(os.path.join(win_dir, filename), os.path.join(win_dir, proj_name + filename[1:]))

            
def replace_file_content(file_name, solution_id, proj_id, proj_name):
    f = open(file_name,'r')
    filedata = f.read()
    f.close()

    newdata = filedata.replace("@PROJ_NAME@", proj_name).replace("@PROJ_UUID@", proj_id).replace("@SOLUTION_UUID@", solution_id)

    f = open(file_name,'w')
    f.write(newdata)
    f.close()
    
def prepare(proj_name, path):
    #generate solution uuid
    solution_id = str(uuid.uuid4()).upper()
    #generate project uuid
    proj_id = str(uuid.uuid4()).upper()
    
    #replace @PROJ_NAME@, @SOLUTION_UUID@ and @PROJ_UUID@
    replace_file_content(os.path.join(path, proj_name, "cmake", "CMakeLists.txt"), solution_id, proj_id, proj_name)
    win_dir = os.path.join(path, proj_name, "win")
    for filename in os.listdir(win_dir):
        f = os.path.join(win_dir, filename)
        replace_file_content(f, solution_id, proj_id, proj_name)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Use app proj_name path")
        print("For example: generate.py A ../cf544div2")
        sys.exit()

    proj_name=str(sys.argv[1])
    out_path=str(sys.argv[2])
    
    copy_template(proj_name, out_path)
    prepare(proj_name, out_path)
   