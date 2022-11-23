import os
import subprocess


from tqdm import tqdm
import logging

from datetime import datetime




def create_folders( output_folder_path):

    if os.path.exists(output_folder_path):
        print(f"{output_folder_path} exist")
    else:
        print(f"{output_folder_path} creation")
        os.makedirs(output_folder_path)


def create_log_file(path_log):

    create_folders(path_log)

    date = datetime.now().date()

    file = f"generation_doc_rst_api_{date}.log"

    file_path = os.path.join(path_log,file)

    logging.basicConfig(filename=file_path,filemode='w', level=logging.DEBUG)

def set_environnement_variables(dict_values):

    for key,value in dict_values.items():

        os.environ[key] = value





class Device:

    def __init__(self, name):

        self.name = name 

    def create_devices(file_devices):
        
        devices = None
        with open(file_devices) as f:
            devices_str = f.readlines()
            
            devices = [ Device(device_str.replace("\n","")) for device_str in devices_str]
            
    
        return devices


    


    def create_doxygen(self, project_name, file_doxygen, input_path_source, output_folder_path_doxygen,input_path_source_CMSIS ):
        
        output_folder_path_doxygen_device = os.path.join(f"{output_folder_path_doxygen}",f"{self.name}")
        project_name_device = os.path.join(f"{project_name}",f"{self.name}")
        
        create_folders(output_folder_path_doxygen_device)
        dict_values_environement ={
            "DEVICE": self.name,
            "INPUT_PATH_SOURCE": input_path_source,
            "PROJECT_NAME_DOXYGEN":project_name_device,
            "OUTPUT_DIRECTORY_XML":output_folder_path_doxygen_device,
            "INPUT_PATH_CMSIS": input_path_source_CMSIS,
            "PATH_DOC_SOURCE": os.getcwd()
        }

        set_environnement_variables(dict_values_environement)

        

        log_file = logging.getLogger().handlers[0].baseFilename

        subprocess.run(["doxygen",file_doxygen])# stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


    def create_api_doc(self, project_name, input_folder_path_doxygen, output_folder_path_rst):

        output_folder_path_rst_device = f"{output_folder_path_rst}_{self.name}"
        input_folder_path_doxygen_device = os.path.join(f"{input_folder_path_doxygen}",f"{self.name}","xml")
        project_name_device = f"{project_name}_{self.name}"

        create_folders(output_folder_path_rst_device)

        log_file = logging.getLogger().handlers[0].baseFilename

        #TODO use the different functions of the apidoc instead of calling subprocess
        print(output_folder_path_rst_device)
        print(repr(input_folder_path_doxygen_device))
        subprocess.run(["breathe-apidoc",input_folder_path_doxygen_device ,f"-o",  f"{output_folder_path_rst_device}",\
            f"-p", f"{project_name_device}" ], cwd=os.getcwd())

    def create_rst_header(self,index_path):
        print(f"Create RST index for API_{self.name} on {index_path}")
        #TODO Change this to a better way 
        with open(f"{index_path}","a") as f_rst:
            text_append = f"""

API for device {self.name}
============================

.. toctree::
    :maxdepth: 1
    
    API_{self.name}/grouplist"""


            f_rst.write(text_append)


        

        
def check_index(index_path):
    with open(f"{index_path}","a") as f_rst:
        print(f_rst.readlines())
    

if __name__ == '__main__':

    # TODO Create a Parser for better implementation

    path_project_base = os.getcwd()
    
    path_file = os.path.dirname(__file__)

    os.chdir(path_file)

    #TODO Create a dict

    path_folder_doxygen = os.path.abspath("../_build/doxygen") 
    path_folder_api = os.path.abspath("API")
    path_index = os.path.abspath("index.rst")
    device_file = os.path.abspath("devices.txt")
    project_name = "STM32Cube"
    file_doxygen = os.path.abspath("doxygenConfiguration_reduced.dox")
    input_path_source = os.path.abspath("../../Drivers/STM32U5xx_HAL_Driver")
    log_path = os.path.abspath("../_log/")
    input_path_source_CMSIS = os.path.abspath("../../Drivers/CMSIS/Device/ST/STM32U5xx/Include")



    print(path_folder_doxygen)
    print(input_path_source)
    print(input_path_source_CMSIS)


    create_log_file(log_path)
    #TODO create a log file with errors


    devices = Device.create_devices(device_file)

    for device in tqdm(devices):
        device.create_doxygen(project_name,file_doxygen, input_path_source, path_folder_doxygen, input_path_source_CMSIS)
        device.create_api_doc(project_name, path_folder_doxygen, path_folder_api)
        device.create_rst_header(path_index)

    check_index(path_index)
    os.chdir(path_project_base)
