# Make Bugs

## Overview

This file contains all the bugs I have encountered when running `make` on my machine, using the repository's Makefile.

## Bugs

### `make: *** No rule to make target 'build/Makefile', needed by 'build'.  Stop.`

This error occurs when you change the structure of the repository, while there is a compiled build of the previous strcuture. To fix this, run `make clean` to remove the compiled build, and then run `make` again.
