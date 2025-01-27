# Makefile for complex

#### 頻繁に変更が必要なもの
# 実装のためのヘッダー(プロトタイム宣言、構造体宣言、定数定義を含む)
HEADER=complex.h

# 作成したい関数が入ったファイル
OBJECTS=complex.o

# 関数のテストが記載されたファイル(3年前期では使わない)
TEST_OBJECTS=

# 最終実行ファイル(名前を修正したら .gitignore も修正すること)
TARGET=complexMain

# 最終実行ファイル(名前を修正したら .gitignore も修正すること)
GRAPH_TARGET=graphMain

# テスト実行ファイル(名前を修正したら .gitignore も修正すること)
TEST_TARGET=testComplex

#### 以下は変更する必要がないもの

# 最終実行ファイルの実名
TARGET_EXE=$(TARGET)$(EXE)
# 最終グラフ実行ファイルの実名
GRAPH_TARGET_EXE=$(GRAPH_TARGET)$(EXE)
# ターゲット実行ファイルの実名
TEST_TARGET_EXE=$(TEST_TARGET)$(EXE)
# 実装のメインファイル main 関数を含む
MAIN=$(TARGET).o
# 実装のメインファイル main 関数を含む
GRAPH_MAIN=$(GRAPH_TARGET).o
# テストのためのヘッダー(プロトタイプ宣言、3年後期では使わない)
#TEST_HEADER=$(TEST_TARGET).h
TEST_HEADER=
# テストのメインファイル main 関数を含む
TEST_MAIN=$(TEST_TARGET).o
# テストに必要なファイル
TEST_COMMON=testCommon.o
# 必要な CFLAGS
CFLAGS=-Wall -g
# 必要なライブラリ
LIBS=-lm
CHCP=

ifeq ($(OS),Windows_NT)
	CC=gcc
	RM=cmd.exe /C del
	EXE=.exe
	CHCP=chcp 65001
else
	RM=rm -f
	EXE=
endif

exec: $(TARGET_EXE) $(PNGS) $(SVGS)
	$(CHCP)
	./$(TARGET_EXE)

graph: $(GRAPH_TARGET_EXE) $(PNGS) $(SVGS)
	$(CHCP)
	./$(GRAPH_TARGET_EXE)

test: $(TEST_TARGET_EXE)
	$(CHCP)
	./${TEST_TARGET_EXE}

$(TARGET_EXE): $(MAIN) $(OBJECTS) $(HEADER)
	$(CHCP)
	$(CC) -o $@ $(CFLAGS) $(MAIN) $(OBJECTS) $(LIBS)

$(GRAPH_TARGET_EXE): $(GRAPH_MAIN) $(OBJECTS) $(HEADER)
	$(CHCP)
	$(CC) -o $@ $(CFLAGS) $(GRAPH_MAIN) $(OBJECTS) $(LIBS)

$(TEST_TARGET_EXE): $(TEST_MAIN) $(OBJECTS) $(TEST_OBJECTS) $(TEST_COMMON) $(HEADER) $(TEST_HEADER)
	$(CHCP)
	$(CC) -o $@ $(CFLAGS) $(TEST_MAIN) $(OBJECTS) $(TEST_OBJECTS) $(TEST_COMMON) $(LIBS)

clean:
	$(RM) $(TARGET_EXE) $(GRAPH_TARGET_EXE) $(TEST_TARGET_EXE) $(MAIN) $(GRAPH_MAIN) $(TEST_MAIN) $(OBJECTS) $(TEST_OBJECTS) $(TEST_COMMON)
