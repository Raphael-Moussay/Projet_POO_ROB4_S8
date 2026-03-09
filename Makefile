# Nom de l'exécutable
EXEC_NAME = run

# Compilateur
CXX = g++

PKG_CONFIG ?= pkg-config
PINOCCHIO_CFLAGS := $(shell $(PKG_CONFIG) --cflags pinocchio eigen3 2>/dev/null)
PINOCCHIO_LIBS := $(shell $(PKG_CONFIG) --libs pinocchio eigen3 2>/dev/null)

# Flags GCC standards
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR) $(PINOCCHIO_CFLAGS)

# Flags des bibliotheques standard et externe
LDLIBS = $(PINOCCHIO_LIBS)

# Dossiers
SRC_DIR = ./src
INC_DIR = ./inc
BIN_DIR = ./bin
BUILD_DIR = ./build

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Chemin de l'exécutable
EXEC = $(BIN_DIR)/$(EXEC_NAME)

# Règle par défaut
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDLIBS)
#@echo "$(CXX) $(OBJS) -o $@ $(LDLIBS)"

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@


# Création des dossiers si nécessaire
makedir: 
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(SRC_DIR)
	mkdir -p $(INC_DIR)

# Nettoyage
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d

aclean: clean
	rm -f $(EXEC)

# Force rebuild
rebuild: aclean all

# Inclusion des dépendances auto-générées
-include $(DEPS)

# Déclaration des règles "virtuelles"
.PHONY: all clean aclean rebuild