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
4. [Open Chart]()：包含如下几个数据集的集合（ChartQA, DVQA, InfoVQA, Pew, and OpenCQA）