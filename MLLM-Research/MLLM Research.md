# 评测数据集和榜单
1. [MLLM-Bench](https://github.com/FreedomIntelligence/MLLM-Bench/tree/main): 提供开源的[图像评测数据集](https://github.com/FreedomIntelligence/MLLM-Bench/tree/main/data)，包含420个复杂图像指令对，主要侧重从感知、理解、应用、分析、评估和创建六个角度评估MLLM的42种能力![](MLLM-Research/Pasted%20image%2020240910103410.png)
2. [Video-MME](https://video-mme.github.io/home_page.html#leaderboard)：视频理解评测数据集和[榜单](https://video-mme.github.io/home_page.html#leaderboard)，包含900条短中长视频，长视频有subtitle；评测数据集显示只能学术研究，需额外申请
3. [MME](https://github.com/BradyFU/Awesome-Multimodal-Large-Language-Models/tree/Evaluation)：第一个MLLM理解能力的评测榜单
4. [P2Med-MD](https://arxiv.org/abs/2409.02608)：包括来自 163,999 名门诊病例和 8,684 名住院病例的真实临床信息。该数据集包括 2D 胸部 X 光图像、3D 胸部 CT 图像、相应的放射学报告以及门诊和住院记录。
5. [SEED-Bench-H](https://huggingface.co/datasets/AILab-CVC/SEED-Bench-H)：图像相关的多选题评估数据集
6. [mPLUG-Owl3](https://github.com/X-PLUG/mPLUG-Owl/tree/main/mPLUG-Owl3)：暂时只开放了一个[单图多模态评测数据集](https://huggingface.co/datasets/StarBottle/mPLUG-Owl3-Evaluation)的合集，TODO表示会开放全部的训练数据集
![](MLLM-Research/QQ_1726197346047.png)
# 训练开源数据集
## 描述类
- [**ShareGPT-4o**](https://huggingface.co/datasets/OpenGVLab/ShareGPT-4o/tree/main)：GPT-4o生成的高质量图像、视频和语音数据集，分别200K、10K和10K

### 图像
1. [**ShareGPT4V**](https://huggingface.co/datasets/Lin-Chen/ShareGPT4V)：GPT-4V生成的图像数据集，共100K，主要以描述解释图像内容为主
2. [**ALLaVA-Caption**](https://huggingface.co/datasets/FreedomIntelligence/ALLaVA-4V)：利用GPT-4V生成细粒度的图像注释、复杂推理指令和详细答案，轻量级的视觉语言模型训练数据集。它包含两个主要子集：ALLaVA-Caption-LAION-4V和ALLaVA-Caption-VFLAN-4V。

### OCR & 程序

### 视频
1. [**ShareGPT4Video**](https://huggingface.co/datasets/ShareGPT4Video/ShareGPT4Video)：由GPT-4V和ShareCaptioner-Video分别生成的300和3000h的视频描述数据集，单个视频平均时长为30s左右，描述文本长度约260词
2. [**ShareGemini**](https://huggingface.co/datasets/Share14/ShareGemini)：应用gemini-1.5-pro API对 ([Webvid](https://github.com/m-bain/webvid), [Kinetic-400](https://github.com/cvdfoundation/kinetics-dataset), [InternVid](https://github.com/OpenGVLab/InternVideo/tree/main/Data/InternVid), [HD-VILA](https://github.com/microsoft/XPretrain/tree/main/hd-vila-100m))等开源视频数据集进行标注
3. [**VCG+ 112K**](https://huggingface.co/datasets/MBZUAI/VCG-plus_112K)：提供了139K基于[VideoInstruct-100K](https://huggingface.co/datasets/MBZUAI/VideoInstruct-100K)数据集，进行改进注释管道和进行关键帧抽取，并利用SOTA多模态模型进行多轮注释标注

## QA
### 图像
1. [**LLaVA-Instruct-150K**](https://huggingface.co/datasets/liuhaotian/LLaVA-Instruct-150K)：为视觉指令微调而创建的，包括150K条由GPT-4生成的多模态指令跟随数据。这些数据主要用于训练模型在图像和语言理解上的表现。数据集由对COCO数据集的图像和语言生成模型交互而生成，包括会话、详细描述和复杂推理等任务。
2. [**WuKong**](https://arxiv.org/abs/2202.06767)：一百万个图像和中英文描述的键值对
3. [**LVIS-Instruct**](https://huggingface.co/datasets/X2FD/LVIS-Instruct4V)：GPT-4V生成的约220K细粒度视觉指令数据集，图像信息来自于[LVIS](https://www.lvisdataset.org/dataset)
4. [**ScienceQA**](https://huggingface.co/datasets/derek-thomas/ScienceQA)：包含21K多模态多选题，包含了多领域多层次解释的科学讲座类问题等，通过CoT等方法引导模型学习多跳问题解释方法

### OCR
1. [**Anyword-3M**](https://modelscope.cn/datasets/iic/AnyWord-3M)：包括一些来自[laion-400m](https://laion.ai/blog/laion-400-open-dataset/)、Wukong等数据集的OCR训练集
2. [**ICDAR2019-LSVT**](https://rrc.cvc.uab.es/?ch=16&com=downloads)：街景文本阅读任务，包含约450000张带有文字标注的图像，其中30000张图像进行了完整标注，400000张图像进行弱标注
3. [**ICDAR2017-RCTW**](https://rctw.vlrlab.net/dataset)：通过手机收集的约12K中文室外识别任务数据集
4. [**Open Chart**]()：包含如下几个数据集的集合（ChartQA, DVQA, InfoVQA, Pew, and OpenCQA）

# MLLM训练流程
## 整体架构
整体来说主要由一个预训练的模态编码器（pre-trained modality encoder）、一个预训练的LLM和一个用于连接他们的模态接口（modality inference）组成，一些特殊的MLLM可能还包括一个生成器（generator）用来生成文本以外的其他模态输出![](MLLM-Research/QQ_1726298244737.png)

### 模态编码器（Modality Encoder）
- 用于将原始信息（如图像和音频）压缩为更紧凑的表示形式

常见的形式是使用已经与其他模态对齐的预训练编码器，如[CLIP](https://arxiv.org/abs/2103.00020)等。一些常用的图像编码器如下：![](MLLM-Research/QQ_1726299608079.png)

在选择编码器时，通常要考虑到分辨率、参数大小以及预训练语料库等因素；相较而言，输入分辨率对编码器质量的影响较大。

许多相关工作都已证实使用更高分辨率图像训练出的编码器可以实现更高的性能增益，而提高输入分辨率主要通过直接缩放（direct scaling）和图像分割（patch division）的方法：
1. 直接缩放：直接将更高分辨率的图像输入到编码器中，通常需要对预训练编码器作进一步处理或者使用更高分辨率的预训练编码器
2. 图像分割：通过将高分辨率图像分割为小的图像块，重复使用低分辨率编码器，并将子图像与下采样的高分辨率图像一同发送到图像编码器，分别捕获图像的局部和全局特征

类似的编码器也可以用于其他模态，例如[ImageBind-LLM](https://arxiv.org/abs/2309.03905)配备的编码器支持对图像、文本、音频、深度、热和惯性测量单元 （IMU） 数据进行编码，可以相应各种模态的输入

### 预训练LLM
现有阶段主要应用Causal-Encoder架构的LLM，通过扩大参数等方式提升性能表现。应用如混合专家模型（MoE），在不增加计算成本的基础上通过选择性激活参数来扩展总参数大小

### 多模态接口（Modality Inference）
因为LLM只能感知文本，因此有必要弥补自然语言与其他模态之间的差距。常用的方法是在预先训练的视觉编码器和LLM之间引入一个可学习的连接器，另一种方式则通过专家模型将图像信息进行描述，再将描述后语言传给LLM

