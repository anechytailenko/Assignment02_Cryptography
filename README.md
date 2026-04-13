# Assignment02_Cryptography

## Authorship and contribution of each of the group members

**Nechytailenko Anna**: found an attack basis using the Autoguess tool, developed a custom C++ simulation to practically demonstrate a Guess-and-Determine attack, along with finding the full internal state and write corresponding report parts.

**Illia Prykhodko**: WRITE HERE

## 1.  Theoretical background of the partial guessing attack and example of its application

**1.1 The essence of the Guess-and-Determine(GD) Attack**

The GD attack is an advanced cryptanalytic technique used against stream ciphers. It optimizes recovery of the internal state by replacing exhaustive brute-force with a structured algebraic approach.

- Precondition: Gamma recovery

    The attack typically begins  with a Known Plaintext Attack. If an adversary possesses both the original (P) and the ciphertext (C), they can isolate the gamma (G) due to the properties of the XOR operation: 

``G = P XOR C``

Once the gamma is known, it serves as the observable data use to solve the cipher's internal equations.

-  Identifying the Guess Basis

    The attacker anayzes the cipher's architecture (like we have done with Strumok) to find the Guess Basis - the smallest possible subset of internal state variables. The goal is to bypass the total state complexitey by focusing only on these internal state variables (in strumok, this comprises the 1024-bit Linear Feedback Shift Register (LFSR), consisting of sixteen 64-bit words (s0​,…,s15​), and the 128-bit Finite State Machine (FSM), consisting of two 64-bit registers (r1​,r2​).)


- The logical sequence 

    The attack executes through a deterministic chain reaction:

        1) Guess: The attacker iterated through all possible values for the variables in the Guess Basis

        2) Determine: Using the intercepted gamma and the cipher's state-transition equations. the remaining state variables are calculated automatically.

        3)  Verify: If the calculated state produces a gamma that matches the subsequent bits of the observed gamma. the cipher is compromised.

- Consequence:

    By exploring these mathematical dependicies, the GD attack reduces the effective security of an algorithm to the complexity of the Guess Basis rather than the full internal state. This often reveals that a cipher is significant weaker than its theoretical declared version.


**1.2. Practical Appliance of GD Attack**

Paritial guessing attacks are a focal point of actice research in modern cryptography. A signficant breakthrough in automating these attacks was presented in the paper "Autoguess: A Tool for Finding Guess-and-Determine Attacks and Key Bridges" (H. Hadipour & M. Eichlseder, ACNS 2022). This work formalized the reduction of finding an attack basis to MILP and SAT-solver problems, enabling discovery of vulnerabilities in numerous establishing ciphers:

1) The SNOW Family (Strumok's predecessor): researches identifies a Guess Basis of 9 words by analyzing 13 initialization clocks. 
2) The AES Block Cypher : for a 2-round version of AES, researchers found that guessing only 10 specific variables is enough to solve the rest of the state. With just one known plain-cypher text, these 10 variables act as a key that unlocks the remaining 6, bypassing the need for a full 2^128 brute-force search.
3) ZUC(used in 4G/LTE): breakthrough involves splitting the 32-bit LFSR state into half-words, by doing this and leveraging Viterbi-like algorithm - the basis was optimised to require only 6 words. Given attacke reached a computational complexity of 2^398
4) ChaCha20: even not using shift registers, the cypher is vulnerable to "Key Bridges" - logial links between intermediate states in the ARX architecture. Because ARX operations are totally inverible, a successful bridge allows calculate both the secret key and the future keystream. By appling Grover's algorithm to these bridges 256-bit security is reduced to 2^251, falling below the theoretical 2^256 limit


## 2. Implementation of Strumok-256 and -512 + benchmark - WRITE HERE

### How to build:

1) ``bash mkdir build``
2) ``bash cd build``
3) ``bash cmake ..``
4) ``bash cmake --build .``

### Run benchmark:
``bash cmake --build . --target run_benchmark``

### Run tests:
``bash cmake --build . --target run_tests``

## 3. Identified Bases for the Guess-and-Determine Attack

To identify the attack basis, a mathematical model of the keystream generation phase of the "Strumok-512" cipher was constructed using the Autoguess tool across 11 clock cycles.



### 3.1 Dependency Graph Optimisation: merging FSM variables

When constructing the mathematical model of the Strumok stream cipher for hte Autoguess tool, a primary challenge is the redudancy of internal states. According to the DSTU 8845:2019 specification, hte FSM utilises two 64-bit registers, r_1^t and r_2^t at each clock cyclte t.

Problem: intriducing every register as an independent unkonwn variable unnecessarily inflated the graph's dimensions and the complexity of the basis search. However, the cipher's architecture allows for a crytanalytic optimisation based on the bijectivity of the non-linear transformation function T. 

Solution: by exploring the property of bijectivity, the FSM states can be logically merged withing the dependency graph. This reduction minimizes the number of the variable the SAT-solver must process, leading to a more efficient identification of the Guess Basis.

**Mathematical Justification**
The update rule for the second FSM register is defined by the following equation:

$r_2^{(t+1)} = T(r_1^{(t)})$

The function T is a composition of S-boc substitution and linear mixing. Its primary cryptographic property is strict bijectivity, meaning it provides a one-to-one mapping that possesses a unique inverse, $T^{-1}$.

Consequently, the state of the first register can be derived from hte second: 

$r_1^{(t)} = T^{-1}(r_2^{(t+1)})$


In a GD context, an attacker does not need to guess variables linked by deterministeic, reversible functions. Knowledge of  $r_1^{(t)}$ provides instantaneous knowledge of $r_2^{(t+1)}$, and vice versa.

**Optimisation: Implementation of a unified variable R**
To streamline the model, we can eliminate the $r_1$  variable by expressing them throug "future" state of  $r_2$. By defining $R_t$ as the state register $r_2$ of at clock cycle $t$ , the variables are substituted as follows: 

* $r_2^{(t)}$ is replaces by  $R_t$
* $r_1^{(t)}$ is replaces by  $R_{t+1}$

### 3.2 Final symmetric connection for Autoguess:

By implementing the substituitions $r_1^{(t)} \rightarrow R_{t+1}$  $r_2^{(t)} \rightarrow R_t$,and steamilining the shift register numbering (where $s_0^{(t)} \rightarrow S_t$), complex formulas of the "Strumok" standard are reduced to three primary Connection Relations for each clock cycle$t$:

1. **LSFR update:** $S_{t+16} = (S_t \otimes \alpha) \oplus (S_{t+11} \otimes \alpha^{-1}) \oplus S_{t+13}$
   * *Connection:* `S_{t+16}, S_{t+13}, S_{t+11}, S_t`
2. **Gamma generation** $Z_t = ((S_{t+15} +_{64} R_{t+1}) \oplus R_t) \oplus S_t$
   * *Connection:* `S_{t+15}, R_{t+1}, R_t, S_t` (The known gamma $Z_t$ is ommited fromm hte dependency graph, as the tool focuses strictly on relationships between unknown variables).
3. **FSM update ($r_1$):** $R_{t+2} = R_t +_{64} S_{t+13}$
   * *Connection:* `R_{t+2}, S_{t+13}, R_t`



### 3.3 Basis search results and detailed attack analysis

To identify the attack basis. a mathematical model of the "Strumok-512" keystream generation phase was constructed over 11 clock cycles using Autoguess tool. The folloinh command was executed in the terminal:

```bash
autoguess --inputfile strumok_11_rounds.txt --solver sat --maxguess 7 --maxsteps 12 --dglayout circo
```
- maxguss 7: limits the Guess Basis to a maximum of seven variables.
- maxsteps 12: sets the computational threshold for the determination chain.

**Mathematical justification: degree of freedom**

The analyzed system consists of 40 unknown variables and only 33 functional equations.This create an algebraic deficit 40-33=7 degree of freedom. To achieve a unique solution for the system, ans attacker must compensate for the gap by correctly guessing exactly 7 independent variables. A smaller basis would leave the system mathematically underdetermined.

**[SAT solver results*](task03/results/output)**

The toll succesfully identifies a viable attack basis: 

- Guess basis(7 variables): $\{S_{16}, R_1, S_3, R_5, S_{20}, S_{21}, S_5\}$
- Attack complexity: $7 \times 64 = 448$ bits of exhaustive search.
- Security impact: The reulting complexity of $2^{448}$ operation thoretically compromises the $2^{512}$ security margin claimes by the standard.

**Graph topology and the "Domino effect"**

The success of the attack relies on the strategic selection of these 7 nodes, which asct as triggers for a continuous chain reaction. According to the [Autoguess repor](task03/results/output), the determiantion process unfolds actoss 12 stages. 

- Stage 0: substituting the 7 guesses variables immediately leaves only one unknown in three seperate equations, allowing for the instant calculation of $R_3, S_{18}$, and $R_6$.

- Stage 1-11: resolved values propagare through the system. For instance, at stage 1, the combination of $R_3$ and $R_1$ reveals $S_{14}$, while $S_{18}$ and $R_5$ reveal $R_7$.

- Stage 11: the final variable, $S_{26}$, is caluclated.


**Conclusion:**
Within 12 casxading steps. the attacker deterministically recovers the entire internal state (``40 out of 40 state variables are known without``) without any further brute-force requirements. The visual propagation path of this detemiantion wave is illustrated in the [dependecy graph](task03/results/output_graph.pdf).



## 4. Practical simulation of the Determination Phase

The objective of this stage is to programmatically validate the feasibility of the theoretical attack on the **Strumok-512** cipher using a custom C++ simulation: ``bash cmake --build . --target run_attack`` - passed test serve as the funcitonal proof of the cryptoanlytic vulnerabilities.

### 4.1 Adversial model and initial data

The simulation is predicted on an adversarial model where the attacker has already obtained the following parameters:
* **Gamma:** 11 intercepted 64-bit words ($Z_0, \dots, Z_{10}$) generated during the cipher's normal operational mode.

* **The attack basis**: a set of 7 correcyly guessed internal variables:  $\{S_{16}, R_1, S_3, R_5, S_{20}, S_{21}, S_5\}$.

### 4.2 Computational logic:

The deterministic recovery of the remaining 33 internal state variable is achieved through a combination of the **Autoguess** determinaion logs and rigorous algebraic reversal of the DSTU 8845:2019 standard specifications.

**1. Operational sequence**
The implementation strictly adheres to the determination cascase identifies in the graph topology spanning from **State 0** to **State 11**. The sequence is optimized such that each line of code calculated a specific variable only after all its functional arguments have been resolved in preceding steps.

**2. Derivation of inverse equation**
While the dependency graph identifies the links between nodes. the simulation requires the derivation of inverse equation to isolate the unkown variable from the standard's forward functions:

* **Register update** The forward state transition $R_{new} = (R_{old} + S) \pmod{2^{64}}$ is inverted using modular substraction to recover previous states.
    * *Implementation:* `R[3] = R[5] - S[16];`
* **State transition** These operations involve matrix $\alpha$-multiplication and XORs. Since XOR is an **involution**, the targer unknown and the known observable are swapped to solve the equation.
    * *Implementation:* `S[18] = S[21] ^ strumok_AlphaMul(S[5]) ^ ...`
* **Gamma output**  The output function  $Z = ((S_{20} + R_6) \oplus R_5) \oplus S_5$ is solved from the **"outside-in."**. By applying inverse XORs followed by modular substraction, the hidden register values are isolated and recovered.
    * *Implementation:* `R[6] = ((Z[5] ^ S[5]) ^ R[5]) - S[20];`


### 4.3 Conclusion

By sequentially traversing the dependency graph and applying these derived inverse equations, the script deterministically recovers 100% of the internal state without the need for additional exhaustive search - thereby confirming the mathematical vulnerability of the cipher.



## 5.  короткий порiвняльний аналiз характеристик шифрiв Струмок iз iншими шифрами,наприклад, шифрами ZUC, ChaCha20 тощо. - WRITE HERE