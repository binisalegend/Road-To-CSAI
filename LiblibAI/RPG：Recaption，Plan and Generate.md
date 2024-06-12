# 整体架构
---
- Multimodal Recaptioning(多模态重述)：将提示词转化为高度描述性的语句，为扩散模型提供信息增强的提示理解。使用LLM将文本提示分解为子提示，再使用更加描述性的表达进行重述；同时使用MLLM自动捕获输入图像，以此分析目标提示词与生成图像之间的语义差异
- Chain-of-Thought Planning(思维链规划)：将整个图像划分为互补的子图像，并为每个区域赋予各自的子提示词，相当于将组合生成任务拆分为多个子任务。借助MLLM的思维链推理能力进行区域划分，并分析重新生成的即时结果，为后续生成提供了更详细精确的指令
- Complementary Regional Diffusion(互补的区域扩散)：在指定子区域内通过子提示独立生成图像，通过调整尺寸和拼接方式进行组合。通过使用基于轮廓的区域扩散，可以精确操控区域进行修改，解决了重叠图像内容问题

## 优势点
1. 无需额外训练的架构模型，最大程度利用扩散模型的组合可控性
2. 使用MLLM通过重现过程中生成的图像，借助思维链不断优化生成指令
3. 互补区域扩散最大程度的精确化编辑图像
4. 对各类多模态模型和扩散架构都很友好

- 整体架构：![](LiblibAI/RPG：Recaption，Plan%20and%20Generate.assets/Pasted%20image%2020240612180155.png)
- 互补区域扩散：提示词拆分与子区域拼接![](LiblibAI/RPG：Recaption，Plan%20and%20Generate.assets/Pasted%20image%2020240612180242.png)
- 借助MLLM进行多轮生成图像分析和提示词精细化![](LiblibAI/RPG：Recaption，Plan%20and%20Generate.assets/Pasted%20image%2020240612175926.png)