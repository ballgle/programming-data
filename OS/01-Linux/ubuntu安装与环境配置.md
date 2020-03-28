# ubuntu(18.x) 安装与配置

## 1 安装 ubuntu

### 双系统

预备设置：windiws关闭快速启动，bios关闭安全启动。

1. U盘启动
2. uefi警告时选择`后退`
3. 分区为：
   - `/Boot`(引导分区) ，1000M ，主分区
   - `/`(根分区) ，30760M ，这里不要设置的太小，毕竟可能安装许多软件
   - 交换分区，8000M。
   - `/home`(用户目录), 剩余所有容量
4. 安装完毕
5. 进入windows10，使用easyBCD添加引导项：`grub2-自动选择`

### 单系统

120G ssd + 1T硬盘：

1. 挂载点：109798（SSD）
1. boot：2046（SSD）
1. swap分区：7986（SSD）
1. home：1000203（SSD）

>UEFI 模式需要单独分一个 200M 左右的区给 EFI，格式为 FAT32，然后把 grub 安装在这个分区。不然会出现错误提示『无法将grub-eif-amd64-signed软件包安装到/target/中』。具体参考[UEFI 模式安装 Win10 + Ubuntu 18.04](https://maajiaa.wordpress.com/2018/05/16/installing-win10-ubuntu-in-uefi/)

---
## 2 ubuntu环境搭建与相关配置

### 配置源

参考 [Ubuntu 18.04换国内源 中科大源 阿里源 163源 清华源](https://blog.csdn.net/xiangxianghehe/article/details/80112149)

### 安装主题与美化

1：安装优化工具

```shell
#安装美化管理器(中文名：优化)
sudo apt install gnome-tweak-tool
```

2：Gnome-shell Extensions

1. 用 firefox 打开 <https://extensions.gnome.org>，按照提示安装插件
2. udo apt install chrome-gnome-shell
3. 安装以下扩展
   1. User Themes
   2. Dash to Dock
   3. Gnome Global Application Menu
   4. TopIcons Plus

3：安装相关主题和图标

- 网址：<https://www.gnome-look.org/>
- 下载相关主题后按照要求提取并放置于指定目录中，一般是`~/.themes` 中
- 推荐的 themes
  - <https://www.opendesktop.org/s/Gnome/p/1013714/>
  - <https://www.opendesktop.org/s/Gnome/p/1013741/>
  - <https://www.opendesktop.org/s/Gnome/p/1102582/>

具体参考：

- [Ubuntu18.04（Gnome桌面）主题美化，Mac私人定制](https://blog.csdn.net/zyqblog/article/details/80152016)
- [Ubuntu18.04 美化](https://www.jianshu.com/p/49ed3971170a)

### install aptitude

aptitude 工具是基于 apt 的一款安装工具，优点是可以自动解决安装和卸载时候的依赖关系。

```shell
sudo apt install aptitude
```

### install Shadowsocks

具体参考[Shadowsocks-Wiki](https://github.com/Shadowsocks-Wiki/shadowsocks)

### install vscode

参考[Installing Visual Studio Code on Ubuntu](https://linuxize.com/post/how-to-install-visual-studio-code-on-ubuntu-18-04/)

更新 VSCode

```shell
sudo apt upgrade code
```

### install jdk

```shell
//open jdk
sudo apt-get update
sudo apt-get install openjdk-8-jdk
```

配置 `JAVA_HOME` 参考 [how-to-set-java-home-for-java](https://askubuntu.com/questions/175514/how-to-set-java-home-for-java)

### oh-my-zsh

```shell
sudo apt-get install zsh
```

具体参考[oh-my-zsh,让你的终端从未这么爽过](https://www.jianshu.com/p/d194d29e488c)

### vim 配置

```shell
sudo apt-get install vim-gtk
```

`vim /etc/vim/vimrc` 编辑配置文件，加入以下配置

```shell
set nu
set tabstop
set cursorline
set ruler
```

### dos2unix

```shell
sudo apt-get install dos2unix
```

### Tomcat

从官网下载tomcat，然后解压即可，远程连接时要开放对应的端口。

```shell
# 创建tomcat存放目录，比如 /usr/local 目录下
cd /usr/local
mkdir tomcat

# 下载tomcat
wget http://mirrors.shu.edu.cn/apache/tomcat/tomcat-8/v8.5.31/bin/apache-tomcat-8.5.31.tar.gz

# 解压
tar -xvf apache-tomcat-8.5.31.tar.gz

# 启动tomcat(记得开放8080端口)
./startup.sh
./shutdown.sh
```

### MySQL

```shell
apt-get update
apt-get install mysql-server mysql-client
测试是否安装成功：netstat -tap | grep mysql

启动MySQL服务：service mysql start
停止MySQL服务：service mysql stop
服务状态：service mysql status
修改 MySQL 的管理员密码：mysqladmin -u root password newpassword

正常情况下，mysql占用的3306端口只是在IP 127.0.0.1上监听，拒绝了其他IP的访问（通过netstat可以查看到）取消本地监需要修改 my.cnf 文件：

  1 vim /etc/mysql/my.cnf，把 bind-address = 127.0.0.1注释掉，如果配置文件中没有bind-address = 127.0.0.1，则添加下面内容：
       [mysqld]
       bind-address = 0.0.0.0
  2 重启MySQL服务器
  3 重新登录 mysql -uroot -p
  4 在mysql命令行中运行下面两个命令
  grant all privileges on *.* to 'root'@'%' identified by '远程登录的密码';
    flush privileges;
  5 检查MySQL服务器占用端口 netstat -nlt|grep 3306

数据库存放目录： /var/lib/mysql/
相关配置文件存放目录：/usr/share/mysql
相关命令存放目录：/usr/bin(mysqladmin mysqldump等命令
启动脚步存放目录：/etc/rc.d/init.d/
```

sql授权说明

语法：`grant 权限1,权限2, ... 权限n on 数据库名称.表名称 to 用户名@用户地址 identified by '连接口令';`

- `权限1，权限2，... 权限n` 代表 `select、insert、update、delete、create、drop、index、alter、grant、references、reload、shutdown、process、file` 等14个权限。
- 当`权限1，权限2，... 权限n` 被 `all privileges` 或者 `all` 代替时，表示赋予用户全部权限。
- 当 `数据库名称.表名称` 被 `*.*` 代替时，表示赋予用户操作服务器上所有数据库所有表的权限。
- 用户地址可以是localhost，也可以是IP地址、机器名和域名。也可以用 `'%'` 表示从任何地址连接。
- '连接口令'，远程连接时使用的密码，不能为空，否则创建失败。

>privileges 即特权的意思。

### 开放端口号

1. Ubuntu 默认有装 iptables，可通过 `which iptables` 确认
2. Ubuntu 默认没有 iptables 配置文件，可通过`iptables-save > /etc/iptables.up.rules`生成
3. 读取配置并生效可以通过  `iptables-restore < /etc/iptables.up.rules`

```shell
#查看哪些端口被打开  
netstat -anp
#查看当前防火墙配置并显示规则行号
iptables -L --line-numbers

#关闭端口号（DROP表示关闭）：
iptables -I INPUT -p tcp --dprop 端口号 -j DROP
iptables -I OUTPUT -p tcp --dport 端口号 -j DROP

#打开端口号（ACCEPT 表示打开）：
iptables -I INPUT -ptcp --dport  端口号 -j ACCEPT
#将修改永久保存到防火墙中：
iptables-save

#关闭/打开防火墙（需要重启系统）
  #开启：
  chkconfig iptables on
  #关闭：
  chkconfig iptables off
```

配置开机启动：vim  `/etc/network/interfaces` 增加

```shell
#启动时应用防火墙  
pre-up iptables-restore < /etc/iptables.up.rules
#关闭时保存防火墙设置,以便下次启动时使用
post-down iptables-save > /etc/iptables.up.rules
```

---
## 引用

- [ss 的安装与配置](https://github.com/Shadowsocks-Wiki/shadowsocks/blob/master/6-linux-setup-guide-cn.md)
- [how-to-install-visual-studio-code-on-ubuntu-18-04/](https://linuxize.com/post/how-to-install-visual-studio-code-on-ubuntu-18-04/)
