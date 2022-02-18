$$
\prod_{i=1}^{n} \prod_{j=1}^{m} f[\gcd(i,j)]=\prod_{d=1}^{\min{n,m}}f[d]^{t(d)}\\

\begin{aligned}
t(d) & =\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=d]\\
&=\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j=1}^{\lfloor \frac{n}{d} \rfloor} [\gcd(i,j)=1]\\
&=\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{k\mid \gcd(i,j)} \mu(k)\\
&=\sum_{k=1}^{\min(\lfloor \frac{n}{d} \rfloor,\lfloor \frac{m}{d} \rfloor)} \mu(k) \sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} [k\mid i] \sum_{j=1}^{\lfloor \frac{n}{d} \rfloor} [k\mid j]\\
&=\sum_{k=1}^{\min(\lfloor \frac{n}{d} \rfloor,\lfloor \frac{m}{d} \rfloor)} \mu(k) \lfloor \frac{n}{kd} \rfloor \lfloor \frac{m}{kd} \rfloor
\end{aligned}
$$
---
$t(d)$ 内可数论分块计算，且 $t(d)$ 的值可数论方块



---
$$
\newcommand\lcm{\operatorname{lcm}}
\begin{aligned}
\prod_{x=1}^{n}\prod_{y=1}^{n}\frac{\lcm(x,y)}{\gcd(x,y)} 

&= \prod_{x=1}^{n}\prod_{y=1}^{n} \frac{xy}{\gcd(x,y)^2}\\

&= \frac{\prod_{x=1}^{n}\prod_{y=1}^{n}xy}{\prod_{x=1}^{n}\prod_{y=1}^{n}\gcd(x,y)^2}
\end{aligned}\\

t(d)=\sum_{k=1}^{\lfloor \frac{n}{d} \rfloor} \mu(k) \lfloor \frac{n}{kd} \rfloor ^ 2\\
=\sum_{d\mid p} \mu(\frac{p}{d}) \lfloor \frac{n}{p} \rfloor^2\\

\prod_{x=1}^{n}\prod_{y=1}^{n} \gcd(x,y)=\prod_{d} d^{t(d)}\\
=\prod_{p} \prod_{d \mid p} d^{\mu(\frac{p}{d}) \lfloor \frac{n}{p} \rfloor^2}\\

=\prod_{p} (\prod_{d \mid p} d^{\mu(\frac{p}{d})}) ^ {\lfloor \frac{n}{p} \rfloor^2}

$$

---

$$
f(n)=\prod_{d \mid n} d^{\mu(\frac{n}{d})}
$$