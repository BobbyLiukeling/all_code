# 慕课网公开课：《Python数据预处理》

本课程是作者跟慕课网合作开发的一款数据预处理课程，归作者和慕课网共同所有，仅限学习使用。

> 技术交流群
机器学习和自然语言（QQ群号：436303759）是一个研究深度学习、机器学习、自然语言处理、数据挖掘、图像处理、目标检测、数据科学等AI相关领域的技术群。其宗旨是纯粹的AI技术圈子、绿色的交流环境。为解决成员交流中的时间壁垒，为提高群体技术交流效率。本群禁止有违背法律法规和道德的言谈举止。群成员备注格式：城市-自命名。微信订阅号：datathinks


## 第一部分：抽取多源数据文本信息

### 第一章：Python数据预处理介绍
- 第一小节：什么是数据预处理
- 第二小节：为什么做这门课
- 第三小节：本课程可以学习到什么
- 第四小节：开发环境说明
- 第五小节：课程体系介绍
- 第六小节：源码获取

### 第二章：抽取文本信息
- 第一小节：常见数据类型与采集策略
- 第二小节：一堆杂乱无章的数据
- 第三小节： 文本抽取的3种方法分析
- 第四小节：Pywin32实现文本格式转换
- 第五小节：抽取Word文本算法实现
- 第六小节：抽取PDF文本算法实现
- 第七小节：文本抽取与编码工具的封装
- 第八小节：批量读取目录文件
- 第九小节：实战案例：遍历文件自动抽取新闻文本


## 第二部分：清洗文本数据

### 第三章：清洗文本信息
- 第一小节：准备30万新闻数据
- 第二小节：Yield生成器
- 第三小节： 递归方法遍历30万新闻
- 第四小节： 高效方法遍历30万新闻
- 第五小节： 正则清洗字符串数据
- 第六小节： 正则清洗网页数据
- 第七小节： 简繁字体转换
- 第八小节：实战案例：高效批量清洗新闻文本数据

### 第四章: 文本特征提取
- 第一小节：结巴分词精讲
- 第二小节：HanLp分词精讲
- 第三小节：自定义去除停用词
- 第四小节：NLTK词频统计
- 第五小节：高低词频选择方法
- 第六小节： 命名实体快捷抽取
- 第七小节： 计算多分类下的TF-IDF值
- 第八小节：实战案例：高效批量提取新闻文本特征


## 第三部分：文本特征向量化

### 第五章：手工实现文本特征向量化
- 第一小节：解析数据文件
- 第二小节：处理数据缺失值
- 第三小节：不均衡数据归一化
- 第四小节： 计算文本相似度
- 第五小节：特征词转文本向量
- 第六小节：词频与逆词频TF-IDF
- 第七小节：词集模型与词袋模型
- 第八小节：实战案例：新闻文本特征向量化

### 第六章: Gensim实现文本特征向量化
- 第一小节：Ginsim介绍
- 第二小节：Ginsim 构造语料词典
- 第三小节：Ginsim统计特征词频
- 第四小节：Ginsim 计算TF-IDF
- 第五小节：LSA潜在语义分析主题实现
- 第六小节： LDA隐含狄利克雷分布主题实现
- 第七小节： RP生成随机映射主题实现
- 第八小节：HDP分层狄利克雷过程主题实现
- 第九小节：实战案例：Gensim实现新闻文本特征向量化

## 第四部分：特征降维与可视化

### 第七章：主成分分析PCA实现特征降维
- 第一小节：数据降维介绍
- 第二小节：二维数据降维
- 第三小节：PCA 算法原理与实现
- 第四小节： PCA降维特征可视化
- 第五小节：特征数据主成分分析
- 第六小节：实战案例：PCA技术实现新闻文本特征降维

### 第八章: Matplotlib数据可视化
- 第一小节：Matplotlib介绍
- 第二小节：Matplotlib绘制折线图
- 第三小节：Matplotlib绘制散点图
- 第四小节：Matplotlib绘制直方图
- 第五小节：Matplotlib绘制复杂图
- 第六小节：Matplotlib绘制3D图


## 第五部分：XGBoost实现网络新闻自动分类
### 第九章: XGBoost实现新闻文本分类
- 第一小节：文本分类概述
- 第二小节：XGBoost概述
- 第三小节：XGBoost官方案例：预测毒蘑菇
- 第四小节：XGBoost 参数介绍
- 第五小节：XGBoost 调参案例：预测糖尿病患者
    - 加载官网比赛数据
    - 训练算法模型
    - 最佳决策树
    - 最佳min_child_weight和max_depth
    - 最佳gamma和subsample
    - 最佳参数与结果分析）
- 第六小节：新闻文本数据预处理全过程
    - 通用方法类库
    - 生成词典模型
    - 生成TF-IDF向量模型
    - 生成LSI主题模型
    - 特征降维与选择模型
- 第七小节：XGBoost构建分类器模型
- 第八小节：XGBoots分类器模型评估
- 第九小节：综合案例：XGBoost实现网络新闻自动分类



# 开源视频共享

本群倡导"AI技术视频共享"项目，纯粹的收集大家珍藏的技术视频资源，汇少成多，更多的服务大家。本群中的技术视频均由成员无偿自愿上传，以供所有共享者学习。择其部分视频供无共享者成员学习，此技术视频属于公益无偿的，仅供个人学习。不可进行商业活动，违者自行承担后果。截止2019年4月10日经过严格视频质量审核通过的视频为8类包括Python Web技术视频3套、大数据技术视频3套、机器学习技术视频3套、深度学习技术视频8套、数据科学视频6套、数据挖掘视频2套、自然语言处理视频6套和图像处理视频2套，共计33套，约1300G。具体如下：

- Python Web技术视频
  - Django网站开发（贡献者：顽主）
  - Python Web开发完整视频（贡献者：顽主）
  - Python最新就业班（贡献者：顽主）
- 大数据技术视频
  - Hadoop44集入门视频（贡献者：数据思维）
  - Hadoop全套视频（贡献者：数据思维）
  - Hadoop实战视频（贡献者：数据思维）
- 机器学习技术视频
  - 吴恩达机器学习视频（贡献者：烟花易冷）
  - 机器学习视频（贡献者：Candymoon）
  - 2017机器学习升级（贡献者：北京-sunboy）
- 深度学习技术视频
  - Tensorflow源码级技术分享（贡献者：数据思维）
  - 深度神经网络算法全套（贡献者：流音）
  - 吴恩达深度学习视频（贡献者：烟花易冷）
  - 神经网络算法与推荐系统实战（贡献者：水上书）
  - 深度学习（贡献者：顽主）
  - 深度学习实战视频-人脸检测（贡献者：张顺）
  - Tensorflow实战视频-文本分类（贡献者：张顺）
  - TensorFlow打造唐诗生成网络（贡献者：张顺）
- 数据科学视频
  - Scrapy爬虫框架进阶课程（贡献者：数据思维）
  - 分布式爬虫实战视频（贡献者：Timothy）
  - Python数据分析与机器学习实战（贡献者：小佐）
  - 廖雪峰商业爬虫（贡献者：顽主）
  - Python量化金融项目（贡献者：顽主）
  - Python数据分析与机器学习实战（贡献者：顽主）
- 数据挖掘视频
  - 大数据数据分析与挖掘（贡献者：顽主）
  - Python3数据分析与挖掘实战（贡献者：顽主）
- 自然语言处理视频
  - 知识图谱视频（贡献者：Candymoon）
  - 自然语言处理（贡献者：微笑，向着太阳）
  - 知识图谱（贡献者：微笑，向着太阳）
  - 机器学习之自然语言处理（贡献者：大白菜）
  - 自然语言处理之序列模型（贡献者：无为而立）
  - 文本挖掘与自然语言处理（贡献者：海蓝你喜欢吗）
- 图像处理视频
  - 中科院图像处理系列课程（贡献者：顽主）
  - 2018深度学习之目标检测  （贡献者：顽主）