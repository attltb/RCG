# Resource Collection Generator (ENG)

Resource Collection Generator(RCG) is a program to make resource collection files which can be used for various programs by reading a text file containing name and path of each resource to collect.





## About

Programs often require resources such as images and sounds in addition to executable code. They are often stored as separate files outside of the executable, usually with their own file format and extensions instead of well-known formats like .png or .mp3 so that users can not view or modify them with ease.

RCG is a program that makes it easier to create these external resource files. The following features are supported:

- It enables one to store multiple resources in one file. This makes it easier for users to manage the program by reducing the number of resource files that the program depends on. Each resource stored has a unique name one can refer to load the resource.
- For some resources, one can change the data format in advance and save it in the format that target programs can use with ease. For example, many programs uses images in the form of a 32-bit per pixel bitmap with four 8-bit channels of blue, green, red, and alpha. This format is provided under the name `Bitmap32`.





## Installation

If you want to build the binary from the source code, follow the steps below.

1. Download and install the latest version of Cmake for your system from https://cmake.org. You can skip this step if Cmake 3.13 or higher is already installed.

2. Download and install the latest version of OpenCV for your system from https://opencv.org. You can skip this step if OpenCV 3.0 or higher is already installed.

3. Clone the GitHub repository (-) or download it as a zip file and extract to any folder you want.

4. Run Cmake-gui, enter the folder where the repository is cloned in (1) and the folder where the project will be installed in (2), and click (3). 

   <img align="left" src="doc\Cmake.eng.png"><br clear="left"/>

5. Select a build system you want to use to build the RCG project. At least one C++ build system must already be installed to pass this step.

6. When the language and other options appear in the Cmake-gui window, select the language and click (3) again. When you're done, click (4) and again when you're done, click (5).

7. Build the RCG project using the build system you choose.

After the build is complete, find the library files of `core`, `imgcodecs`, and `imgproc` packages (provided with a .dll extension for Windows) in the folder where OpenCV is installed, and copy them to the folder where the program is installed. You should be able to execute the binary after everything is done.





## How to use

### 1) How to create resource collection file

To create a resource collection file, one need data files, such as images, sounds, etc., that he want to store in the resource file. A text file that specifies how to create a resource from them is also required. 

In the text file, information about each resource item that will be included in the resource collection file is entered. The following figure shows how to define one resource item.

<img align="left" src="doc\TextSample.eng.png"><br clear="left"/>

(1) is a name that will be refered by target programs to load this resource. It must be entered and cannot be duplicated.

(2) is absolute or relative paths to the files to be stored in the resource. At least one path must be entered, and if multiple paths are entered, multiple data are saved in an array form.

(3) is used when one want to change the data format of the resources before saving. If omitted, the entire files are saved in binary form without format change. Please refer to the following table for currently supported formats.

| Format name | Information                                                  | Required source                   |
| ----------- | ------------------------------------------------------------ | --------------------------------- |
| Bitmap32    | A 32-bit bitmap with blue, green, red, and alpha (opacity) stored in 8-bit channels each. | Image files (.bmp, .png, .jpg...) |

A single resource is usually defined on a single line, but line breaks may be necessary for readability if you need to store multiple resources as an array. If you need a line break, put the escape character \\ at the end of the line. However, line breaks inside the path are not allowed.

After writing the text file, connect the created file to the RCG executable and run it. On Windows, simply dragging the text file onto the executable will work. You will get a resource collection file with *.dat* extension.



### 2) How to load resources?

Resources created through RCG can be loaded and used in other C++ projects that include the header and source files in the *src_loader* folder via `load` method of the `ResourceCollection` class defined in *ResourceCollection.hpp.* See the example below.

```c++
#include "ResourceCollection.hpp"
void someFunction() {
    ResourceCollection rc;
    ResourceCollection::ERR_CODE errNo = rc.load("resources.dat");
    
    std::vector<SomeFormat*> SomeNamedResources = rc.getSomeFormatResource("SomeName");
   	...
}
```

For other usage and various details, please refer to the actual source files in the *src_loader* folder.






## Contributors

<a href="https://github.com/attltb"><img src="https://avatars.githubusercontent.com/u/77376670?v=4" width="100px;" alt=""/></a>

<a href="https://github.com/attltb">attltb</a> - Program design, coding, etcs.

Contributions of any kind welcome.
