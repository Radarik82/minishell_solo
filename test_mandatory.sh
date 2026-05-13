#!/bin/bash
# Mandatory minishell test suite

SHELL_BIN="./minishell"
PASS=0
FAIL=0
ERRORS=()

# Strip readline prompt lines, heredoc prompt lines, and the exit echo
filter() {
	grep -v '^minishell>' | grep -v '^> ' | grep -v '^exit$'
}

run() {
	local desc="$1"
	local input="$2"
	local expected="$3"

	actual=$(printf "%s\n" "$input" | "$SHELL_BIN" 2>/dev/null | filter)
	if [ "$actual" = "$expected" ]; then
		echo "  PASS  $desc"
		PASS=$((PASS + 1))
	else
		echo "  FAIL  $desc"
		printf "        expected: |%s|\n" "$expected"
		printf "        actual:   |%s|\n" "$actual"
		FAIL=$((FAIL + 1))
		ERRORS+=("$desc")
	fi
}

run_exit() {
	local desc="$1"
	local input="$2"
	local expected_code="$3"

	printf "%s\n" "$input" | "$SHELL_BIN" 2>/dev/null >/dev/null
	actual_code=$?
	if [ "$actual_code" = "$expected_code" ]; then
		echo "  PASS  $desc (exit=$actual_code)"
		PASS=$((PASS + 1))
	else
		echo "  FAIL  $desc (expected=$expected_code got=$actual_code)"
		FAIL=$((FAIL + 1))
		ERRORS+=("$desc")
	fi
}

sep() { echo; echo "── $1 ──────────────────────────────"; }

# ── ECHO ────────────────────────────────────────────────────────────────────
sep "echo"
run "echo simple"              "echo hello"           "hello"
run "echo multiple args"       "echo hello world"     "hello world"
run "echo -n no newline"       "echo -n hi"           "hi"
run "echo empty"               "echo"                 ""
run "echo -n alone"            "echo -n"              ""
run "echo single quotes"       "echo 'hello world'"   "hello world"
run "echo double quotes"       'echo "hello world"'   "hello world"
run "echo quoted empty"        "echo ''"              ""
run "echo no expand single"    "echo '\$HOME'"        '$HOME'
run "echo expand double"       'echo "$HOME"'         "$HOME"
run "echo dollar question"     "true
echo \$?"        "0"
run "echo after false"         "false
echo \$?"        "1"

# ── PWD ─────────────────────────────────────────────────────────────────────
sep "pwd"
run "pwd matches cwd"  "pwd"  "$(pwd)"

# ── CD ──────────────────────────────────────────────────────────────────────
sep "cd"
run "cd /tmp then pwd"       "cd /tmp
pwd"                               "/tmp"
run "cd ~ goes home"          "cd ~
pwd"                               "$HOME"
run "cd no arg goes home"     "cd
pwd"                               "$HOME"
run "cd - goes back"          "cd /tmp
cd $PWD
cd -
pwd"                               "/tmp"

# ── EXPORT / UNSET / ENV ────────────────────────────────────────────────────
sep "export / unset / env"
run "export sets var"         'export TESTVAR=hello
echo $TESTVAR'                     "hello"
run "unset removes var"       'export TESTVAR=hello
unset TESTVAR
echo $TESTVAR'                     ""
run "env contains HOME"       "env | grep '^HOME='"    "HOME=$HOME"
run "export visible in env"   'export MYVAR=42
env | grep "^MYVAR="'           "MYVAR=42"

# ── $? exit status ───────────────────────────────────────────────────────────
sep "exit status (\$?)"
run "true = 0"        "true
echo \$?"            "0"
run "false = 1"       "false
echo \$?"            "1"
run "bad cmd = 127"   "nonexistentcmd123
echo \$?"            "127"
run "echo = 0"        "echo hi
echo \$?"            "hi
0"

# ── QUOTES ──────────────────────────────────────────────────────────────────
sep "quotes"
run "single no expand"      "echo '\$USER \$HOME'"   '$USER $HOME'
run "double expands USER"   'echo "$USER"'            "$USER"
run "mixed quotes"          "echo 'a'\"b\"'c'"        "abc"
run "empty single"          "echo ''"                 ""
run "empty double"          'echo ""'                 ""
run "space in single"       "echo 'a   b'"            "a   b"

# ── PIPES ────────────────────────────────────────────────────────────────────
sep "pipes"
run "simple pipe"       "echo hello | cat"              "hello"
run "pipe to grep"      "printf 'a\nb\nc\n' | grep b"  "b"
run "three-stage pipe"  "echo hello | cat | cat"        "hello"
run "cat pipe wc -w"   "echo hello | wc -w"             "$(echo hello | wc -w)"

# ── REDIRECTIONS ─────────────────────────────────────────────────────────────
sep "redirections"
TMPF="/tmp/ms_test_$$"

run "redirect out >"        "echo hello > $TMPF
cat $TMPF"                       "hello"

run "redirect append >>"   "echo line1 > $TMPF
echo line2 >> $TMPF
cat $TMPF"                       "line1
line2"

run "redirect in <"        "echo world > $TMPF
cat < $TMPF"                     "world"

run "redirect truncates"   "echo first > $TMPF
echo second > $TMPF
cat $TMPF"                       "second"

rm -f "$TMPF"

# ── HEREDOC ──────────────────────────────────────────────────────────────────
sep "heredoc (<<)"
run "basic heredoc cat"     "cat << EOF
hello
world
EOF"                               "hello
world"

run "heredoc single-line"   "cat << EOF
only
EOF"                               "only"

run "heredoc quoted no expand"  "cat << 'EOF'
\$HOME
EOF"                               '$HOME'

run "heredoc unquoted expand"   "cat << EOF
\$HOME
EOF"                               "$HOME"

run "heredoc in pipeline"   "cat << EOF | grep hello
hello
world
EOF"                               "hello"

run "heredoc with echo before" "echo start
cat << END
line1
line2
END"                               "start
line1
line2"

# ── SYNTAX / EDGE CASES ──────────────────────────────────────────────────────
sep "syntax / edge cases"
run "empty input"           ""                ""
run "whitespace only"       "   "             ""
run "many spaces between"   "echo  a  b"      "a b"

# ── EXIT CODE ────────────────────────────────────────────────────────────────
sep "exit code"
run_exit "exit 0"    "exit 0"    0
run_exit "exit 42"   "exit 42"   42
run_exit "exit 255"  "exit 255"  255

# ── SUMMARY ──────────────────────────────────────────────────────────────────
echo
echo "══════════════════════════════════════════"
echo "  Results: $PASS passed, $FAIL failed / $((PASS + FAIL)) total"
if [ ${#ERRORS[@]} -gt 0 ]; then
	echo "  Failed tests:"
	for e in "${ERRORS[@]}"; do echo "    - $e"; done
fi
echo "══════════════════════════════════════════"
