# Nom de l'exécutable
EXEC_NAME = run

# Compilateur
CC = g++

# Récupération des flags via pkg-config (Pinocchio inclut déjà Eigen3)
PKGS = pinocchio eigen3
PKG_CFLAGS = $(shell pkg-config --cflags $(PKGS))
PKG_LIBS = $(shell pkg-config --libs $(PKGS))

# Dossiers
SRC_DIR = ./src
INC_DIR = ./inc
BIN_DIR = ./bin
BUILD_DIR = ./build

# Flags GCC standards 
# Ajout de PKG_CFLAGS pour les headers externes
CFLAGS = -Wall -Wextra -std=c++17 -pedantic -g -I$(INC_DIR) $(PKG_CFLAGS) -MMD -MP

# Flags des bibliothèques : Ajout de GTest et des libs Pinocchio 
LDLIBS = $(PKG_LIBS) -lgtest -lgtest_main -lpthread

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Chemin de l'exécutable
EXEC = $(BIN_DIR)/$(EXEC_NAME)

# Règle par défaut
all: $(EXEC)
	@echo "\033[32m --- Compilation terminée avec succès --- \033[37m"

# Compilation de l'exécutable (Ordre critique : objets AVANT les libs)
$(EXEC): $(OBJS) | $(BIN_DIR)
	@echo "\033[36m Création de l'exécutable : $@ \033[37m"
	@$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "\033[33m Compilation de $< \033[37m"
	@$(CC) $(CFLAGS) -c $< -o $@

# Création des dossiers
makedir: 
	mkdir -p $(BUILD_DIR) $(BIN_DIR) $(SRC_DIR) $(INC_DIR)

# Nettoyage
clean:
	@echo "\033[31mSuppression des objets \033[37m"
	@rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d

aclean: clean
	@echo "\033[31mSuppression de l'exécutable \033[37m"
	@rm -f $(EXEC)

# Force rebuild
rebuild: clean all

# Inclusion des dépendances auto-générées
-include $(DEPS)

.PHONY: all clean aclean rebuild makedir