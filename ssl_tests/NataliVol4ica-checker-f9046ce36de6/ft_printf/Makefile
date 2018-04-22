
RES_DIR = ./resources
SHORT_EXE_DIR = ./executables
EXE_DIR = $(RES_DIR)/$(SHORT_EXE_DIR)
SHORT_EXE_TESTERS_DIR = $(SHORT_EXE_DIR)/testers
EXE_TESTERS_DIR = $(EXE_DIR)/$(SHORT_EXE_TESTERS_DIR)
TOOLS_DIR = $(RES_DIR)/tools
TOOLS_OBJ_DIR = $(TOOLS_DIR)/obj
SHORT_TESTER_DIR = ./generated_testers
TESTER_DIR = $(RES_DIR)/$(SHORT_TESTER_DIR)
RESULTS = $(RES_DIR)/testing_results
C_SCRIPTS = $(RES_DIR)/c_scripts
BASH_SCRIPTS = $(RES_DIR)/bash_scripts

TOOLS = default_tools \
		differ_tools \
		errors \
		list_tools \
		read_line_tools
C_TOOLS = $(patsubst %, $(TOOLS_DIR)/%.c, $(TOOLS))
O_TOOLS = $(patsubst %, $(TOOLS_OBJ_DIR)/%.o, $(TOOLS))

# COLORS

RED = '\033[0;31m'
GREEN = '\033[0;32m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

all:
	@make clean
	@make mkfilemaker
	@make run_mkfilemaker
	@make testmaker
	@echo ${GREEN}"[Creating testers]"${NC}
	@make -C $(TESTER_DIR)/ create_testers
	@make -C $(TESTER_DIR)/ compile_testers
	@make run_test
	@make run_differ

test:
	@rm -rf $(EXE_DIR)/testers || true
	@mkdir $(EXE_DIR)/testers
	@make -C $(TESTER_DIR)/ compile_testers
	@make run_test
	@make run_differ

clean:
	@echo ${GREEN}"[Removing old obj]"${NC}
	@rm -rf $(TOOLS_OBJ_DIR)
	@echo ${GREEN}"[Recreating testers folder]"${NC}
	@rm -rf $(TESTER_DIR) || true
	@mkdir $(TESTER_DIR)
	@echo ${GREEN}"[Recreating results folder]"${NC}
	@rm -rf $(RESULTS) || true
	@mkdir $(RESULTS)
	@echo ${GREEN}"[Recreating exe folders]"${NC}
	@rm -rf $(EXE_DIR) || true
	@mkdir $(EXE_DIR)
	@mkdir $(EXE_DIR)/testers

# DIFFERENCE FINDER

differ:
	@echo ${CYAN}"[Compiling differ]"${NC}
	@gcc -o $(EXE_DIR)/check_difference $(C_SCRIPTS)/check_difference.c $(O_TOOLS) -I$(TOOLS_DIR)

run_differ:
	@make differ
	@make -C $(TESTER_DIR)/ diff

# TEST

run_test:
	@make -C $(TESTER_DIR)/ run_testers

# TESTMAKER

testmaker: $(TOOLS_OBJ_DIR) $(O_TOOLS)
	@echo ${CYAN}"[Compiling testmaker]"${NC}
	@gcc -o $(EXE_DIR)/testmaker $(C_SCRIPTS)/testmaker.c $(O_TOOLS) -I$(TOOLS_DIR)

# MKFILEMAKER

mkfilemaker: $(TOOLS_OBJ_DIR) $(O_TOOLS)
	@echo ${CYAN}"[Compiling mkfilemaker]"${NC}
	@gcc -o $(EXE_DIR)/mkfilemaker $(C_SCRIPTS)/mkfilemaker.c $(O_TOOLS) -I$(TOOLS_DIR)

run_mkfilemaker:
	@echo ${PURPLE}"[Running mkfilemaker]"${NC}
	@$(EXE_DIR)/mkfilemaker $(SHORT_TESTER_DIR) $(SHORT_EXE_DIR) $(SHORT_EXE_TESTERS_DIR)

# TOOLS

$(TOOLS_OBJ_DIR)/%.o: $(TOOLS_DIR)/%.c
	@gcc -o $@ -c $< -I$(TOOLS_DIR)

$(TOOLS_OBJ_DIR):
	@echo ${GREEN}"[Creating $(TOOLS_OBJ_DIR)]"${NC}
	@mkdir $(TOOLS_OBJ_DIR)

# GETLIB

getlib:
	@rm libftprintf.a || true
	#@make -C ../../ft_printf re
	@cp ../../ft_printf/libftprintf.a .
