#!/bin/bash
# Generates output/tests.txt comparing bash vs minishell for 100 inputs

SHELL_BIN="./minishell"
OUT="output/tests.txt"
> "$OUT"

N=0

msfilter() {
	grep -v '^minishell>' | grep -v '^> ' | grep -v '^exit$'
}

# Standard test: captures stdout+stderr from both shells
T() {
	local desc="$1" input="$2"
	N=$((N + 1))
	bash_out=$(printf '%s\n' "$input" | bash 2>&1)
	ms_out=$(printf '%s\n'   "$input" | "$SHELL_BIN" 2>&1 | msfilter)
	{
		printf '══ Test %3d ══════════════════════════════════════════════\n' "$N"
		printf 'DESCRIPTION : %s\n' "$desc"
		printf '\n1. INPUT:\n%s\n' "$input"
		printf '\n2. BASH OUTPUT:\n'
		[ -z "$bash_out" ] && printf '(empty)\n' || printf '%s\n' "$bash_out"
		printf '\n3. MINISHELL OUTPUT:\n'
		[ -z "$ms_out"   ] && printf '(empty)\n' || printf '%s\n' "$ms_out"
		printf '\n'
	} >> "$OUT"
}

# Exit-code test: records $? instead of stdout
TE() {
	local desc="$1" input="$2"
	N=$((N + 1))
	printf '%s\n' "$input" | bash          >/dev/null 2>&1; bcode=$?
	printf '%s\n' "$input" | "$SHELL_BIN"  >/dev/null 2>&1; mcode=$?
	{
		printf '══ Test %3d ══════════════════════════════════════════════\n' "$N"
		printf 'DESCRIPTION : %s\n' "$desc"
		printf '\n1. INPUT:\n%s\n' "$input"
		printf '\n2. BASH OUTPUT:\nexit code: %d\n' "$bcode"
		printf '\n3. MINISHELL OUTPUT:\nexit code: %d\n' "$mcode"
		printf '\n'
	} >> "$OUT"
}

# ─────────────────────────────────────────────────────────────────────────────
# SECTION HEADER helper
# ─────────────────────────────────────────────────────────────────────────────
SEC() { printf '\n\n████  %s  ████\n\n' "$1" >> "$OUT"; }

# ─────────────────────────────────────────────────────────────────────────────
# 1-15  ECHO
# ─────────────────────────────────────────────────────────────────────────────
SEC "ECHO (tests 1-15)"

T "echo: simple string"                       'echo hello'
T "echo: multiple arguments"                  'echo hello world'
T "echo: suppress newline (-n)"               'echo -n hi'
T "echo: no arguments"                        'echo'
T "echo: only -n flag"                        'echo -n'
T "echo: single-quoted string"                "echo 'hello world'"
T "echo: double-quoted string"                'echo "hello world"'
T "echo: empty single quotes"                 "echo ''"
T "echo: single quotes prevent expansion"     "echo '\$HOME'"
T "echo: double quotes allow expansion"       'echo "$HOME"'
T "echo: multi-flag -nnn"                     'echo -nnn foo'
T "echo: two commands (no trailing newline)"  $'echo -n hello\necho world'
T "echo: spaces inside double quotes"         'echo "  spaces  "'
T "echo: mixed single and double quotes"      "echo 'a'\"b\"'c'"
T "echo: USER variable expansion"             'echo "$USER"'

# ─────────────────────────────────────────────────────────────────────────────
# 16-17  PWD
# ─────────────────────────────────────────────────────────────────────────────
SEC "PWD (tests 16-17)"

T "pwd: print working directory"              'pwd'
T "pwd: after cd to /tmp"                     $'cd /tmp\npwd'

# ─────────────────────────────────────────────────────────────────────────────
# 18-27  CD
# ─────────────────────────────────────────────────────────────────────────────
SEC "CD (tests 18-27)"

T "cd: tilde expands to HOME"                 $'cd ~\npwd'
T "cd: no argument goes home"                 $'cd\npwd'
T "cd: absolute path /var"                    $'cd /var\npwd'
T "cd: then back with cd -"                   $'cd /tmp\ncd /var\ncd -\npwd'
T "cd: exit status on success"                $'cd /tmp\necho $?'
T "cd: exit status on failure"                $'cd /nonexistentdir123\necho $?'
T "cd: parent directory .."                   $'cd /tmp\ncd ..\npwd'
T "cd: nested path /usr/bin"                  $'cd /usr/bin\npwd'
T "cd: HOME then back"                        $'cd ~\ncd /tmp\ncd ~\npwd'
T "cd: update OLDPWD chain"                   $'cd /tmp\ncd /var\ncd -\ncd -\npwd'

# ─────────────────────────────────────────────────────────────────────────────
# 28-35  EXIT STATUS
# ─────────────────────────────────────────────────────────────────────────────
SEC "EXIT STATUS \$? (tests 28-35)"

T "exit status: true = 0"                     $'true\necho $?'
T "exit status: false = 1"                    $'false\necho $?'
T "exit status: nonexistent command = 127"    $'nonexistentcmd123\necho $?'
T "exit status: echo = 0"                     $'echo hi\necho $?'
T "exit status: /bin/ls success = 0"          $'/bin/ls / > /dev/null\necho $?'
T "exit status: /bin/ls bad path"             $'/bin/ls /badpath123 2>/dev/null\necho $?'
T "exit status: false then true = 0"          $'false\ntrue\necho $?'
T "exit status: true then false = 1"          $'true\nfalse\necho $?'

# ─────────────────────────────────────────────────────────────────────────────
# 36-50  EXPORT / UNSET / ENV
# ─────────────────────────────────────────────────────────────────────────────
SEC "EXPORT / UNSET / ENV (tests 36-50)"

T "export: set and echo variable"                  $'export TESTVAR=hello\necho $TESTVAR'
T "export: unset removes variable"                 $'export TESTVAR=hello\nunset TESTVAR\necho $TESTVAR'
T "export: env shows HOME"                         "env | grep '^HOME='"
T "export: new var visible in env"                 $'export MYVAR=42\nenv | grep \'^MYVAR=\''
T "export: overwrite existing variable"            $'export X=first\nexport X=second\necho $X'
T "export: empty value"                            $'export EMPTYVAR=\necho "$EMPTYVAR"'
T "export: multiple vars on one export line"       $'export A=1 B=2 C=3\necho $A $B $C'
T "export: unset non-existent var (exit 0)"        $'unset NOVAR_XYZ\necho $?'
T "export: number string value"                    $'export NUM=42\necho $NUM'
T "export: value with spaces (quoted)"             $'export SPACED="hello world"\necho $SPACED'
T "export: chain overwrites"                       $'export V=1\nexport V=2\nexport V=3\necho $V'
T "export: no-args shows declare -x format"        $'export SHOWME=test\nexport | grep \'^declare -x SHOWME\''
T "export: alphabetical order (Z A M sequence)"    $'export ZTEST=z\nexport ATEST=a\nexport MTEST=m\nexport | grep TEST'
T "env: PATH variable is set"                      "env | grep '^PATH=' | head -1 | cut -c1-5"
T "env: USER variable is set"                      "env | grep '^USER='"

# ─────────────────────────────────────────────────────────────────────────────
# 51-60  QUOTES
# ─────────────────────────────────────────────────────────────────────────────
SEC "QUOTES (tests 51-60)"

T "quotes: single quotes block all expansion"  "echo '\$USER \$HOME'"
T "quotes: double quotes expand USER"           'echo "$USER"'
T "quotes: mixed single/double concatenated"   "echo 'a'\"b\"'c'"
T "quotes: empty single quotes"                "echo ''"
T "quotes: empty double quotes"                'echo ""'
T "quotes: spaces preserved in single"         "echo 'a   b'"
T "quotes: spaces preserved in double"         'echo "a   b"'
T "quotes: variable inside double quotes"      $'export VAR=hello\necho "value: $VAR"'
T "quotes: dollar-question in double quotes"   $'true\necho "status: $?"'
T "quotes: no expansion in single quotes"      "echo 'no \$expansion here'"

# ─────────────────────────────────────────────────────────────────────────────
# 61-70  PIPES
# ─────────────────────────────────────────────────────────────────────────────
SEC "PIPES (tests 61-70)"

T "pipe: echo to cat"                   'echo hello | cat'
T "pipe: printf to grep"                "printf 'a\nb\nc\n' | grep b"
T "pipe: three-stage cat chain"         'echo hello | cat | cat'
T "pipe: echo to wc -w"                 'echo hello | wc -w'
T "pipe: sort strings"                  "printf 'banana\napple\ncherry\n' | sort"
T "pipe: tr uppercase to lowercase"     "echo HELLO | tr 'A-Z' 'a-z'"
T "pipe: tail last line"                "printf 'line1\nline2\nline3\n' | tail -1"
T "pipe: four-stage chain"              'echo foo | cat | cat | cat'
T "pipe: grep matching pattern"         "printf 'apple\nbanana\napricot\n' | grep '^a'"
T "pipe: count words in echo"           'echo hello world foo | wc -w'

# ─────────────────────────────────────────────────────────────────────────────
# 71-82  REDIRECTIONS
# ─────────────────────────────────────────────────────────────────────────────
SEC "REDIRECTIONS (tests 71-82)"

P="/tmp/ms_redir_$$"

T "redirect: > creates and writes file"        "echo hello > ${P}1
cat ${P}1"

T "redirect: >> appends second line"           "echo line1 > ${P}2
echo line2 >> ${P}2
cat ${P}2"

T "redirect: < reads stdin from file"          "echo world > ${P}3
cat < ${P}3"

T "redirect: > truncates existing file"        "echo first > ${P}4
echo second > ${P}4
cat ${P}4"

T "redirect: < with wc -w"                    "echo hello world > ${P}5
wc -w < ${P}5"

T "redirect: multi-line append (3 lines)"      "echo alpha > ${P}6
echo beta >> ${P}6
echo gamma >> ${P}6
cat ${P}6"

T "redirect: pipe result into file"            "echo piped | cat > ${P}7
cat ${P}7"

T "redirect: count lines with wc -l"           "echo a > ${P}8
echo b >> ${P}8
echo c >> ${P}8
wc -l < ${P}8"

T "redirect: grep from redirected file"        "echo hello world > ${P}9
grep hello < ${P}9"

T "redirect: cat file into another file"       "echo source > ${P}10
cat < ${P}10 > ${P}11
cat ${P}11"

T "redirect: chain > then cat"                 "echo chain > ${P}12
cat ${P}12 | wc -c"

T "redirect: > with number content"            "echo 42 > ${P}13
cat ${P}13"

rm -f "${P}"[0-9]*

# ─────────────────────────────────────────────────────────────────────────────
# 83-88  HEREDOC
# ─────────────────────────────────────────────────────────────────────────────
SEC "HEREDOC << (tests 83-88)"

T "heredoc: basic two-line body"               $'cat << EOF\nhello\nworld\nEOF'
T "heredoc: single-line body"                  $'cat << EOF\nonly\nEOF'
T "heredoc: quoted delimiter blocks expansion" $'cat << \'EOF\'\n$HOME\nEOF'
T "heredoc: unquoted delimiter expands vars"   $'cat << EOF\n$HOME\nEOF'
T "heredoc: piped to grep"                     $'cat << EOF | grep hello\nhello\nworld\nEOF'
T "heredoc: after regular command"             $'echo start\ncat << END\nline1\nline2\nEND'

# ─────────────────────────────────────────────────────────────────────────────
# 89-95  EXTERNAL COMMANDS
# ─────────────────────────────────────────────────────────────────────────────
SEC "EXTERNAL COMMANDS (tests 89-95)"

T "external: /bin/echo"                        '/bin/echo test'
T "external: /bin/true exit status"            $'/bin/true\necho $?'
T "external: /bin/false exit status"           $'/bin/false\necho $?'
T "external: tr via full path"                 '/usr/bin/tr a-z A-Z <<< hello'
T "external: whoami"                           'whoami'
T "external: hostname"                         'hostname'
T "external: echo piped to external wc"        'echo one two three | /usr/bin/wc -w'

# ─────────────────────────────────────────────────────────────────────────────
# 96-100  EXIT CODE (measures actual $? of the shell process)
# ─────────────────────────────────────────────────────────────────────────────
SEC "EXIT CODE — shell process (tests 96-100)"

TE "exit: exit 0 → shell exits 0"    'exit 0'
TE "exit: exit 1 → shell exits 1"    'exit 1'
TE "exit: exit 42 → shell exits 42"  'exit 42'
TE "exit: exit 127 → shell exits 127" 'exit 127'
TE "exit: exit 255 → shell exits 255" 'exit 255'

# ─────────────────────────────────────────────────────────────────────────────
printf '\n\nTotal tests generated: %d\n' "$N" >> "$OUT"
echo "Done — output/tests.txt written ($N tests)"
