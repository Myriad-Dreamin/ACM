IO
- IO-01 GET_CHAR/READ/READA/READC/READF/READL/READS

存储结构
- DS-01 链式前向星
- 


算法结构


$\displaystyle T(n)\approx O(\frac{\sqrt{n}}{\log n})+T(\frac{6n}{\pi^2})=O(\frac{\sqrt{n}}{\log n})+T(\frac{n}{\tau})\\$
$\displaystyle T(\tau^k)\approx O(\frac{\tau^{k/2}}{k\log \tau})+T(\tau^{k-1})=O(\frac{1}{\log \tau}\sum_{i=1}^{k}\frac{\tau^{i/2}}{i})$
根据$\displaystyle f(x)=\frac{a^x}{x},f'(x)=(\ln a-\frac{1}{x})\frac{a^x}{x}>0$
$\displaystyle 所以O(\frac{1}{\log \tau}\sum_{i=1}^{k}\frac{\tau^{i/2}}{i})\lt O(\frac{1}{\log \tau}k\frac{\tau^{k/2}}{k})=O(\frac{1}{\log \tau}\tau^{k/2})$

$\displaystyle n=\tau^k\Rightarrow k=\frac{\log n}{\log \tau}$
$\displaystyle \begin{aligned}T(n)=&T(\tau^k)=O(\frac{1}{\log \tau}\tau^{k/2})=O(\frac{1}{\log \tau}\tau^{\log n/(2\log\tau)})=O(\frac{1}{\log \tau}\mathrm{pow}(2,\frac{\log n\log \tau}{2\log \tau}))=O(\frac{\sqrt{n}}{\log \tau})=O(\sqrt{n})\end{aligned}$
