

int main(void)
{
	// 创建流式套接字
	socket();

	// 绑定本地地址
	bind();

	// 处于监听状态
	listen();

	// 接收连接请求
	int newsd = accept();

	// read() / write()

	close();

	exit(0);
}

