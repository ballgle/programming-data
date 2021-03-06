# 软件安装与管理

## 1 包的格式：rpm 和 deb

为什么有两种呢？因为 Linux 现在常用的有两大体系，一个是 CentOS 体系，一个是 Ubuntu 体系，前者使用 rpm，后者使用 deb。

## 2 软件的安装与管理：dpkg 与 rpm

在 Linux 上面，没有双击安装这一说，因此想要安装，我们还得需要命令。

- CentOS 下面使用`rpm -i jdk-XXX_linux-x64_bin.rpm`进行安装
- Ubuntu 下面使用`dpkg -i jdk-XXX_linux-x64_bin.deb`。其中 -i 就是 install 的意思。

列出已安装软件：

- 凭借 `rpm -qa` 和 `dpkg -l` 就可以查看安装的软件列表，-q 就是 query，a 就是 all，-l 的意思就是 list。
- 常用命令示例：`rpm -qa | more`、`rpm -qa | less`、`dpkg -l | grep jdk`。

软件的卸载：

- 如果要删除，可以用`rpm -e`和`dpkg -r`。-e 就是 erase，-r 就是 remove。

## 3 Linux 的软件管家：apt-get 与 yum

CentOS 下面是 yum，Ubuntu 下面是 apt-get。

- rpm 由 RedHat 公司开发，Fedora、CentOS、SuSe等Linux发行版使用其管理软件安装。yum 是基于 rpm 的在线升级机制。
- dpkg 机制最早由 Debian Linux 社区开发出来，派生于 Debian 的 Linux 发行版本大多使用 dpkg 这个机制来管理软件，比如 ubantu、B2D 等，apt-get 是 dpkg 的在线升级机制。

安装 JDK：

- `yum install java-11-openjdk.x86_64`
- `apt-get install openjdk-9-jdk`

卸载 JDK：

- `yum erase java-11-openjdk.x86_64`
- `apt-get purge openjdk-9-jdk`

## 4 apt-get 详细使用

配置源：

- 首先备份原始的文件：`sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup`。
- 配置镜像：<https://mirrors.tuna.tsinghua.edu.cn/>，选择好对应的平台和版本，覆盖 `/etc/apt/sources.list` 中的文件即可。

apt-get常用命令：

```shell
sudo apt-get update  更新源
sudo apt-get install package 安装包
sudo apt-get remove package 删除包
sudo apt-cache search package 搜索软件包
sudo apt-cache show package  获取包的相关信息，如说明、大小、版本等
sudo apt-get install package --reinstall   重新安装包
sudo apt-get -f install   修复安装
sudo apt-get remove package --purge 删除包，包括配置文件等
sudo apt-get build-dep package 安装相关的编译环境
sudo apt-get upgrade 更新已安装的包
sudo apt-get dist-upgrade 升级系统
sudo apt-cache depends package 了解使用该包依赖那些包
sudo apt-cache rdepends package 查看该包被哪些包依赖
sudo apt-get source package  下载该包的源代码
sudo apt-get clean && sudo apt-get autoclean 清理无用的包
sudo apt-get check 检查是否有损坏的依赖
```

## 4 配置环境变量

可以通过 export 命令配置：

```shell
export JAVA_HOME=/root/jdk-XXX_linux-x64
export PATH=$JAVA_HOME/bin:$PATH

# 将配置持久化
source .bashrc
```

export 命令仅在当前命令行的会话中管用，一旦退出重新登录进来，就不管用了，如果想要永久配置，则可以配置在 `.hashrc` 中，在当前用户的默认工作目录，例如 `/root` 或者 `/home/username` 下面，有一个.bashrc 文件，每次登录的时候，这个文件都会运行，因而把它放在这里。这样登录进来就会自动执行。当然也可以通过 `source .bashrc` 手动执行。

## 4 软件安装位置

apt-get 下载后，软件所在路径是什么：`/var/cache/apt/archives`，ubuntu 默认的PATH为：`PATH=/home/brightman/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games`

**apt-get install安装目录是包的维护者确定的，不是用户**。

`dpkg -L 软件包的名字`，获取这个软件包包含了哪些文件。

- 系统安装软件一般在 `/usr/share`
- 文档一般在 `/usr/share`
- 可执行文件 `/usr/bin`
- 配置文件 `/etc`
- lib文件 `/usr/lib`

## 5 wget 下载软件

使用 wget 可以下载软件，然后手动解压。

## 6 运行软件

### 直接运行

Linux 不是根据后缀名来执行的。它的执行条件是这样的：只要文件有 x 执行权限，都能到文件所在的目录下，通过./filename运行这个程序。当然，如果放在 PATH 里设置的路径下面，就不用./ 了，直接输入文件名就可以运行了，Linux 会帮你找。

### 后台运行

- nohup命令。这个命令的意思是 no hang up（不挂起），也就是说，当前交互命令行退出的时候，程序还要在。
- 在命令行命令的最后加上 &，就表示该程序不能独占当前窗口的交互命令行，而是应该在后台运行。

示例：

```shell
# “1”表示文件描述符 1，表示标准输出，“2”表示文件描述符 2，意思是标准错误输出，“2>&1”表示标准输出和错误输出合并到 out.file 里。
nohup command >out.file 2>&1 &

# 关闭上面命令启动的程序
# ps -ef 可以单独执行，列出所有正在运行的程序。
# awk 工具可以很灵活地对文本进行处理，这里的 awk '{print $2}'是指第二列的内容，是运行的程序 ID。
# 然后通过 xargs 传递给 kill -9，也就是发给这个运行的程序一个信号
ps -ef |grep 关键字  |awk '{print $2}'|xargs kill -9
```

### 以服务方式运行

Linux 也有相应的服务，这就是程序运行的第三种方式，以服务的方式运行。例如常用的数据库 MySQL，就可以使用这种方式运行。

在 ubuntu上：

- `apt-get install mysql-server` 的方式安装 MySQL，然后通过命令 `systemctl start mysql`启动 MySQL，通过`systemctl enable mysql`设置开机启动。之所以成为服务并且能够开机启动，是因为在 `/lib/systemd/system` 目录下会创建一个 `XXX.service` 的配置文件，里面定义了如何启动、如何关闭。

在 CentOS 上（MySQL 被 Oracle 收购后，因为担心授权问题，改为使用 MariaDB，它是 MySQL 的一个分支。）

- 通过命令 `yum install mariadb-server mariadb` 进行安装，命令 `systemctl start mariadb` 启动，命令 `systemctl enable mariadb` 设置开机启动。同理，会在 `/usr/lib/systemd/system` 目录下，创建一个 `XXX.service` 的配置文件，从而成为一个服务。

## 引用

- [Ubuntu(Debian)的aptitude与apt-get的区别和联系](http://www.cnblogs.com/yuxc/archive/2012/08/02/2620003.html)
