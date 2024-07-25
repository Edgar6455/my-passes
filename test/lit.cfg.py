import os
import lit.formats

config.name = 'MyPasses'

config.test_format = lit.formats.ShTest()
config.suffixes = ['.ll']

# Root paths for tests
config.test_source_root = os.path.dirname(__file__)
config.test_exec_root = os.path.join(config.test_source_root, 'Output')

# Ensure the output directory exists
os.makedirs(config.test_exec_root, exist_ok=True)

# Get the LLVM_DIR environment variable and append /build/bin to it
llvm_dir = os.getenv("LLVM_DIR", "/bin")
llvm_bin_dir = os.path.join(llvm_dir, "build", "bin")

# Ensure the required tools are found and substituted
config.substitutions.append(('%opt', os.path.join(llvm_bin_dir, 'opt')))
config.substitutions.append(('%FileCheck', os.path.join(llvm_bin_dir, 'FileCheck')))
config.environment['PATH'] = os.path.pathsep.join([llvm_bin_dir, config.environment.get('PATH', '')])

# Set the root directory of the project by going up one level from the config file's directory
root_dir = os.path.abspath(os.path.join(config.test_source_root, ".."))

# Set the directory where the shared library is located
shlib_dir = os.path.join(root_dir, "lib")

# Define the `%shlibdir` variable
config.substitutions.append(('%shlibdir', shlib_dir))
