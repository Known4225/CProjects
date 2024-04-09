# UFC Summer Style 😎
A project proposal for summer UFC development\
Set to take place AFTER the UFC successfully flies at SA Cup
## Goals:
- Homogenize UFC codebase
- Increase clarity, readability, consistency
- Standardize naming scheme
- Make it easier for new members to get a quicker grasp on the codebase

## Community feedback:
### Slack polls:
<table>
<tr><td>

| Should ternaries be allowed?  |
| :---                          |
| 🔲 Yes                       |
| 🔲 No                        |

</td><td>

| Variable and Function names      |
| :---                             |
| 🔲 variableName, functionName   |
| 🔲 variableName, function_name  |
| 🔲 variable_name, functionName  |
| 🔲 variable_name, function_name |

</td><td>

| Allow C++ reference types (uint32_t& type)  |
| :---                                   |
| 🔲 Yes                                |
| 🔲 No, just use pointers              |

</td></tr>
</table>

All suggestions are welcome!

---
# Initiatives

The various initiatives of the UFC Summer Style 😎 Project.

## Leaner and Meaner:
Remove extraneous includes where possible. If a file doesn't use any of the functions of a header, then don't have it include that header.\
I would recommend starting from the bottom up. Start with headers that many files include, and once all extraneous includes are removed from them, then focus on bigger files.\
Organize the order of #include statements alphabetically (and AFTER the header guard):
```
#ifndef RFD_DRIVER_H
#define RFD_DRIVER_H

#include "buffer_manager.h"
#include "errors.h"
#include "init_if.h"
#include "packets.h"
#include "radio_card_settings.h"
#include "stm32h7xx_hal.h"
```
Or categorize includes if applicable:
```
#ifndef PERI_MULTI_SPI_H
#define PERI_MULTI_SPI_H

/* HW-Specific #includes */
#include "sensor_card_settings.h"
#include "stm32h7xx_hal.h"

/* Card-Specific #includes */
#include <cstring>

/* UFC Core #includes */
#include "multispi_if.h"
```
## Tried and Tested:
A testing file can contain (hardware and flight) tests or (nonflight) tests.\
Testing files with the _ut suffix indicate (hardware and flight) tests.\
Testing files with the _st suffix indicate (nonflight) tests.

Testing files contain function declarations and definitions, not classes.\
Testing functions should return void and make use of the check() assert to log errors to the console.\
For files with hardware and flight tests, place the flight tests above the hardware ones, with the principle run_flight_tests_Name(); function at the very top.

## Marco's Macros
Embedded systems programming has a lot of unavoidable macro usage throughout the code.

### Naming Macros
Many user-created macros have specific uses, often in only one file. You should prefix these macros with their respective domains
```
#define I3G4250D_REG_ID			0x0F
#define I3G4250D_REG_CTRL1		0x20
#define I3G4250D_REG_CTRL2		0x21
#define I3G4250D_REG_CTRL3		0x22
#define I3G4250D_REG_CTRL4		0x23
#define I3G4250D_REG_CTRL5		0x24
```
Remember that macros have a global scope, you may not be the only one with a CTRL1 register

### Macros vs Functions
In general, prefer functions over macros. There is very little reason to use a macro as a function. It is more confusing, more error prone, and the performance difference is typically negligable. If you really want to use a macro as a function, consider inlining your function instead.

Macro responsibly! #️⃣

## Classes and Inheritance
I'm not sure I'm qualified to speak on this one

### Naming
A class name looks like this:
```
class GPIO_Stm32h7xx {
    // class things
};
```
### Inherited classes
```
class Multispi_Sensors : public MultiSpiIF {
    // class things
};
```
### Private and public fields and methods
Since many flight and non-flight tests call would-be private functions and access would-be private variables. The general solution has been to just make most fields and methods public.

## Documentation
If you come across a file that you have no idea what it does, it's a perfect candidate for documentation.\
Basically try to figure out a high level description of what it does, and put that in the Notes section of the header comment. If the original author is still around, they can probably provide a lot of insight and maybe you can get them to document the file and its functions.\
In general, try to document files and functionality you create as much as possible. You don't need to document every function, maybe just ones that someone using your code would want to know. Try to document files though, just something small in the notes section should be good to get a description of what the purpose of the file is. You can also throw any relevant links to datasheets, forum posts, or other material that could be useful to someone continuing development on the file.

## General style guidelines
- Indents should be four spaces
- Use K&R style brackets
- Always include curly braces around conditionals and loops
- Stay away from one letter variables, only use them for iterators
- In general, use the int32 type for iterators, always use stdint types
- Do not use C++ reference arguments, use pointers instead (remove if the people like reference types. I really hope they don't though)
- Use conditionals instead of ternaries (remove if the people like ternaries)
- Do not use static classes or class attributes
- Whitespace guide:
```
uint32_t assignment = 0;
uint32_t *pointerAssignment = NULL;
assignment += 3;
assignment--;
functionCall(arg1, arg2);
GenericClass objectCreation(arg1, arg2, arg3);
objectCreation.field1 = 12;
pointerToObject->field1 = 15;
uint32_t *castedObject = (uint32_t *) &object;

if (condition == true) {
    // code
} else {
    // other code
}

for (int32 i = 0; i < 24; i++) {
    // code
}

void functionDefinition(pktHeader_t *ph, uint32_t pkt_len) {
    // code
}

/* line comment on it's own line */
// this is also fine, but if you comment out a big block it might do // // this

GPIO_TypeDef* port; // comment appended to a line of code

/*
Multi-line comment:
STM IDE likes to add a bunch of
*
*
*
which is fine I guess
*/
```

There are of course exceptions to any rule. Just make sure any exceptions are justified.

### Specific Domains

## Drivers
Standard driver formatting

## Flight tests
How to structure a flight test function?




# Questions to be answered (polls?)
- underscores, camel case, naming style
- C++ references
- ternaries yes/no?
- Should enums be allowed?
- should single letter variables be allowed?


## Some thoughts/Rationale
Why disallow things? In a language as old and as large as C++ there are often many ways of doing the same thing. Sometimes these different ways have distinctions that make them more appropriate, performant, or just fit better for a certain subset of problems. The problem is that people have to learn everything in order to do anything. Nobody can know the exact best method for every situation, but what we can know is a standard approach. Here are my thoughts:
### In cases where the compiler is going to generate the same thing in multiple cases, we should just pick one
Examples:
- Ternaries
- References (probably)

In these cases the difference only exists for you, the person reading the code, not for the computer. So it seems obvious to me that we should just pick the more broad and generic solution.

### There are cases where it compiles to different code, but the result is the same or very similar
This is the case for:
- static instances
- const variables
- enums
- inline functions

With these it's a little more tricky. They have uses, but often there is a more generic solution, like macros rather than const variables and macros rather than enums and macros instead of inline functions. But that's just it isn't it. We don't want to use macros for everything, especially for inline functions, so at the end of the day some arbitrary decision will have to be made.

What should be a macro, what should be a function, what should be a class? Do we want datatypes without methods? How many times do we have to copy code before it makes sense to abstract it? Why are constructors so confusing even after 3 years of C++ programming? WHY CAN I SPELL BJARNE STROUSTRUP CORRECTLY ON THE FIRST TRY OH MY GOD HE'S IN MY DREAMS. There's a lot of questions without concrete answers. I'm more tired than I thought I'd be...