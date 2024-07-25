# Assignment: Writing LLVM Passes

Objective: Design and develop LLVM passes to accomplish the following tasks:

1) Print the names of functions encountered in the input module. 
2) Print the basic block count for each function.
3) Print instructions for each basic block. 
4) Print the LLVM IR opcodes encountered in the input module. 
5) Count direct function calls at compile-time (static analysis). 
6) Replace all instances of a specific instruction (e.g., add) with another instruction (e.g., sub).

Resources: [LLVM Tutor](https://github.com/banach-space/llvm-tutor)


## Installation and Setup
This is a **CMake** project.

To build this project, you can simply run bash script ***build.sh*** in the directory `scripts`. 
This will make directory `bin` in the project with an executable file, directory `lib` with necessary **.so** files,
to run the passes with them.

Additionally, there are 2 other bash scripts in the `scripts` directory that can help:

- ***install_dependencies.sh***:  This script installs the necessary dependencies for LLVM development, 
including essential build tools, CMake, Git, Python, and Lit. After that it downloads and installs the 18.x release
from the LLVM source and sets the `$LLVM_DIR` environment variable in the user's .bashrc file.

- ***run-passes.sh***: This script builds the project using ***build.sh*** script, generates LLVM IR for ***example.c***
  file set by default, and runs each pass one by one, showcasing examples of how to use the passes.


## Usage

After building the project, you will have the following passes available:

- 1_functions
- 2_basic-blocks-count
- 3_instructions-in-bb
- 4_opcodes
- 5_function-calls-count
- 6_add-to-sub

There are a couple of ways to run these passes.

### Running directly:
You will be able to run passes using command `opt`. Shared libraries for each pass will be available in `lib` directory.
Example command format:
```bash
opt -load-pass-plugin <path_to_corresponding_lib> --passes=<pass_name> -disable-output <input_file>
```

### Executable ***run_pass***:
In the `bin` directory you will find the ***run_pass*** binary executable. It takes 2 arguments: the pass name and
the path of the LLVM IR input file. Example command: 
```bash
./run_pass 1_functions /path/to/input.ll
```
The executable will run the specified pass. It also shows list of the available passes.


## Testing
To ensure the correct functionality of the LLVM passes, I have integrated `lit` (LLVM Integrated Tester) for automated 
testing. Ensure that you have installed `lit` (it is installed automatically with 
***install-dependencies.sh***). To run the tests, use the following command:

```bash
lit <project_build_dir>/test
```

`lit` will execute each test file, apply the specified LLVM pass, and compare the output against the expected results.
This setup helps ensure that any changes to the LLVM passes are automatically validated for correctness.
