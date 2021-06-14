EXE  =	safeME.exe	
DEBUG =  yes
CXX = g++

# dir
SRC_DIR =       src
INC_DIR =       inc
OBJ_DIR =       obj

# sources
PROJ_SRC_LIST = utils.cpp \
				aes.cpp \
				io.cpp \
				interface.cpp \
				reader.cpp

# headers
PROJ_INC_LIST = $(PROJ_SRC_LIST:.cpp=.hpp)

PROJ_SRC_LIST += main.cpp

# objects
PROJ_OBJ_LIST = $(PROJ_SRC_LIST:.cpp=.o)

#paths
PROJ_SRC =		$(addprefix $(SRC_DIR)/, $(PROJ_SRC_LIST))
PROJ_INC =		$(addprefix $(SRC_INC)/, $(PROJ_INC_LIST))
PROJ_OBJ =		$(addprefix $(OBJ_DIR)/, $(PROJ_OBJ_LIST))

ifeq ($(DEBUG),yes)
CXXFLAGS = -std=c++17 -Wall -g -Wextra #-ansi -pedantic -Weffc++ 
else
CXXFLAGS = -std=c++11 -w -Wall -Werror -s -O2
endif

#libs
IFLAGS =	-I./inc/ 
LFLAGS =	-L./lib/
LDLIBS = 	


all :		 	$(EXE)

#Creating .exe with .o
$(EXE) :    $(PROJ_OBJ)
	@$(CXX) $(LFLAGS) $(LDLIBS) $^ -o $@   
	@echo "Compiling "$(EXE)
	


# Creating .o with .cpp and libs
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(shell mkdir obj)
	@$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@   
	@echo "Compiling" $<

clean :
	@echo "Cleaning Object"
	@$(shell rmdir /S /Q obj)

fclean :	    clean
	@echo "Removing Binary"
	@$(shell rm $(EXE))

re :		    fclean all

.PHONY :	    all, clean, fclean, re

.SILENT :
