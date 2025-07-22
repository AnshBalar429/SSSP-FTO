### Steps of the algorithms are : 

1. **Shortest‑path preliminaries**
2. **Landmark sampling and its guarantees**
3. **The three preprocessing phases**
4. **How queries are answered via a 3‑case split**
5. **Space/time trade‑off and why $\alpha\le\frac12$**
6. **Fast “is‑edge‑on‑path” checks via LCA**

---

## 1. Shortest‑path preliminaries

* We fix a source $s$ and run a vanilla BFS on $G$ to build a **shortest‑path tree** (SPT) rooted at $s$.
* For any vertex $v$, let $\mathrm{dist}(s,v)$ be its (unique, lexicographically minimal) shortest‑path length.
* Every edge $e=(u\!\to\!w)$ in the SPT satisfies

  $$
    \mathrm{dist}(s,w) = \mathrm{dist}(s,u)+1.
  $$

If $e$ is *not* on the SPT, then removing $e$ can never *increase* the distance from $s$ to a target $t$ — the BFS‑tree path remains intact.  That means:

> **Quick check:** If $e\notin$ the SPT‑path from $s\to t$, answer simply $\mathrm{dist}(s,t)$.

Checking “is $e$ on the tree‑path $s\to t$?” can be done in $O(1)$ time per query by preprocessing an LCA structure on the SPT.

---

## 2. Landmark sampling

The *hard* case is when your failed edge $e$ *is* on the SPT‑path to $t$.  Then you need a *detour*.  The oracle’s idea is:

> Insert a small set of “waypoints” (landmarks) along every possible detour.

We pick each vertex to be a **landmark** independently with probability

$$
  p = n^{-\alpha},\qquad 0<\alpha\le\tfrac12.
$$

* Expected number of landmarks $\;|L| = n\,p = n^{1-\alpha}.$
* By a standard sprinkling argument, **every** long path of length $\ell\gg n^\alpha$ *will* hit at least one landmark with high probability.

That means: if you fail an edge *far out* along the path, the detour must re‑join the original tree at some landmark not too far back.

---

## 3. Preprocessing phases

We build three tables:

1. **$\mathrm{dist}(s\!\to\!\ell\mid\neg e)$** for *every* edge $e\in E$ and *every* landmark $\ell\in L$.

   * Interpretation: “If $e$ is deleted, how far is $s$ from $\ell$?”
   * Computed by running one BFS *per edge* (deleting that edge) and reading off distances to all $\ell$.
   * Space: $O(m\cdot |L|)$.

2. **$\mathrm{dist}(\ell\!\to\!v)$** for every landmark $\ell$ and *every* vertex $v$.

   * Just BFS from each $\ell$ in the *undeleted* graph.
   * Space: $O(|L|\cdot n)$.

3. **First‑two‑landmark pointers** on the *failure‑free* shortest‑path from $s\to v$.

   * For each $v$, record $\ell_1$ := first landmark you hit walking from $s$ to $v$ in the SPT, and $\ell_2$ := second one.
   * This lets us know *which* landmark lies “just after” the failed edge.

Together, these give us **constant‑time look‑ups** of any of the above distances.

---

## 4. Answering a query $\bigl(t,e=(u\!\to\!w)\bigr)$

1. **Quick‑path check (LCA):**
   If $e$ is *not* on the SPT‑path from $s\to t$, return $\mathrm{dist}(s,t)$ immediately.

2. **Otherwise** $e$ *is* on the path.  Let $\ell_1,\ell_2$ be the first and second landmarks on the *original* path $s\to t$.  There are three cases for where $e$ “breaks” the path:

   | Case | Geometric picture                        | Detour uses landmark   | Cost lookup                                                                      |
   | ---- | ---------------------------------------- | ---------------------- | -------------------------------------------------------------------------------- |
   |  1   | $e$ lies *before* $\ell_1$               | $\ell_1$               | $\mathrm{dist}(s\to\ell_1\mid\neg e)\;+\;\mathrm{dist}(\ell_1\to t)$             |
   |  2   | $e$ lies *between* $\ell_1$ and $\ell_2$ | $\ell_2$               | $\mathrm{dist}(s\to\ell_2\mid\neg e)\;+\;\mathrm{dist}(\ell_2\to t)$             |
   |  3   | $e$ lies *after* $\ell_2$                | *some* landmark in $L$ | $\min_{\ell\in L}\{\mathrm{dist}(s\to\ell\mid\neg e)+\mathrm{dist}(\ell\to t)\}$ |

3. **Take the minimum** of these three candidate detours.  Since each lookup is $O(1)$ (except the “min over $L$” in Case 3 which is $O(|L|)=O(n^{1-\alpha})$), the total query time is

   $$
     O\bigl(n^{1-\alpha}\bigr)\quad\text{worst‑case.}
   $$

---

