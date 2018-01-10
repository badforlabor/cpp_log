
### 分类日志
c++实现。很简单。


### 即将开发功能
ini配置日志分级。
printf功能支持：自己解析%s，%d等，然后自己处理。这样更安全。由于编译期无法检查安全性，那么可以在运行期处理。比如printf("%s", int)，那么实际将执行itoa(int)
logf功能支持：类似这种logf("param1:{0}, param2:{1}, param1:{0}", p1, p2); 运行期间将所有的参数（p1,p2)转成string，替换给{0}，{1}等。
更省事的宏。比如：PARAM_STR(a)	-> "a":a；再比如PARAM_CLASS(cls, cls_member1, cls_member2)，调用此宏之后，类就支持转string了。额，这个只能依赖c++11了












