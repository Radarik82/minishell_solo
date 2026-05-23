#!/bin/bash
# Generates output/envtest.txt — export/env/unset comparison bash vs minishell

SHELL_BIN="./minishell"
OUT="output/envtest.txt"
> "$OUT"

N=0

msfilter() {
	grep -v '^minishell>' | grep -v '^> ' | grep -v '^exit$'
}

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

SEC() { printf '\n\n████  %s  ████\n\n' "$1" >> "$OUT"; }

# ── EXPORT: basic set ────────────────────────────────────────────────────────
SEC "EXPORT — basic set / read"

T "set and echo"                        $'export VAR=hello\necho $VAR'
T "overwrite existing"                  $'export VAR=first\nexport VAR=second\necho $VAR'
T "empty value"                         $'export VAR=\necho "$VAR"'
T "value with spaces"                   $'export VAR="hello world"\necho $VAR'
T "multiple vars on one line"           $'export A=1 B=2 C=3\necho $A $B $C'
T "export then unset then echo"         $'export VAR=hello\nunset VAR\necho $VAR'
T "number as value"                     $'export NUM=42\necho $NUM'
T "var with underscore in name"         $'export MY_VAR=test\necho $MY_VAR'
T "chain assignment"                    $'export V=1\nexport V=2\nexport V=3\necho $V'
T "export no-value (mark for export)"   $'export NOVAL\necho $?'

# ── EXPORT: no-arg output (declare -x format, alphabetical) ─────────────────
SEC "EXPORT — no-arg output (declare -x, alphabetical order)"

T "single var declare format"           $'export SHOWME=hello\nexport | grep \'^declare -x SHOWME\''
T "Z before A before M — must sort"    $'export ZVAR=z\nexport AVAR=a\nexport MVAR=m\nexport | grep \'VAR\''
T "numbers in name sort correctly"      $'export B2=two\nexport B10=ten\nexport B1=one\nexport | grep \'^declare -x B\''
T "empty value in declare format"       $'export EMPTY=\nexport | grep \'^declare -x EMPTY\''
T "value with spaces in declare format" $'export SPACED="hello world"\nexport | grep \'^declare -x SPACED\''
T "10 vars sorted alphabetically"       $'export J=j\nexport A=a\nexport G=g\nexport D=d\nexport I=i\nexport B=b\nexport H=h\nexport E=e\nexport C=c\nexport F=f\nexport | grep \'^declare -x [A-J]=\''

# ── EXPORT: visible in env ───────────────────────────────────────────────────
SEC "EXPORT — visibility in env"

T "exported var appears in env"         $'export MYVAR=42\nenv | grep \'^MYVAR=\''
T "unexported var absent from env"      $'export MYVAR=42\nunset MYVAR\nenv | grep \'^MYVAR=\''
T "HOME present in env"                 "env | grep '^HOME='"
T "USER present in env"                 "env | grep '^USER='"
T "PATH present in env"                 "env | grep '^PATH=' | head -1 | cut -c1-5"
T "overwritten var updated in env"      $'export KEY=old\nexport KEY=new\nenv | grep \'^KEY=\''

# ── UNSET ────────────────────────────────────────────────────────────────────
SEC "UNSET"

T "unset removes var"                   $'export VAR=hello\nunset VAR\necho $VAR'
T "unset exit status = 0"              $'unset NOEXIST\necho $?'
T "unset multiple vars"                $'export A=1\nexport B=2\nunset A B\necho $A $B'
T "unset then re-export"               $'export VAR=first\nunset VAR\nexport VAR=second\necho $VAR'
T "unset does not affect other vars"   $'export A=keep\nexport B=remove\nunset B\necho $A'

# ── ENV ──────────────────────────────────────────────────────────────────────
SEC "ENV builtin"

T "env with no args shows vars"         "env | grep '^HOME=' | wc -l"
T "env shows exported var"              $'export ENVTEST=yes\nenv | grep \'^ENVTEST=\''
T "env does not show unset var"         $'export GONE=yes\nunset GONE\nenv | grep \'^GONE=\' | wc -l'
T "env shows PATH"                      "env | grep '^PATH=' | wc -l"
T "env exit status = 0"                $'env > /dev/null\necho $?'

printf '\n\nTotal tests: %d\n' "$N" >> "$OUT"
echo "Done — output/envtest.txt written ($N tests)"
