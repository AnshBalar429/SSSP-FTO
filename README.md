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


