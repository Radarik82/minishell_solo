#!/usr/bin/env python3
"""Parse output/tests.txt and write to output/failtest.txt only tests
where BASH OUTPUT != MINISHELL OUTPUT (any deviation counts as a fail)."""

import re

with open("output/tests.txt", "r") as f:
    content = f.read()

# Split on test headers; each element starts with '══ Test N'
raw = re.split(r'(?=══ Test\s+\d+)', content)

STOP = r'(?=\n══|\n████|\nTotal tests|\Z)'

fails = []

for block in raw:
    if not re.match(r'══ Test\s+\d+', block.strip()):
        continue

    m_b = re.search(r'\n2\. BASH OUTPUT:\n(.*?)\n\n3\. MINISHELL OUTPUT:', block, re.DOTALL)
    m_m = re.search(r'\n3\. MINISHELL OUTPUT:\n(.*?)' + STOP, block, re.DOTALL)

    if not m_b or not m_m:
        continue

    bash_out = m_b.group(1).rstrip('\n')
    mini_out = m_m.group(1).rstrip('\n')

    if bash_out != mini_out:
        # Build a clean block: strip embedded section headers (████ lines)
        clean = re.sub(r'\n\n████[^\n]*████\n\n', '\n', block)
        fails.append(clean.rstrip('\n'))

with open("output/failtest.txt", "w") as f:
    if not fails:
        f.write("All 100 tests match bash output exactly.\n")
    else:
        f.write(f"FAILED TESTS  ({len(fails)} / 100 deviate from bash)\n")
        f.write("=" * 60 + "\n\n")
        for blk in fails:
            f.write(blk)
            f.write("\n\n")
        f.write(f"\nTotal failures: {len(fails)}\n")

print(f"Done — {len(fails)} failing tests written to output/failtest.txt")
