---
layout: default
transition: fade
hideInToc: true
---

# 目录

<div class="deck-rule"></div>

<div class="deck-lead">
  整场答辩走一条主线：项目目标与功能边界 → 架构与核心数据 → 交互实现 → 测试、构建与现场演示。
</div>

<div class="split-2">
  <div class="deck-stage">
    <Toc columns="2" minDepth="1" maxDepth="1" />
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">第 1 段</div>
      <div class="rail-title">项目目标与功能</div>
      <div class="rail-copy">项目概述、需求与目标、功能总览。说明系统能做什么、范围怎么收敛。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">第 2 段</div>
      <div class="rail-title">架构与核心数据</div>
      <div class="rail-copy">四层架构、ShapeData 边界、继承体系、策略模式、依赖注入。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">第 3 段</div>
      <div class="rail-title">交互、质量、现场</div>
      <div class="rail-copy">事件分发、图形绘制、I/O、选中变换、测试、构建、演示。</div>
    </div>
  </div>
</div>

<!--
各位老师，我把内容切成三段。第一段先把项目是什么、目标是什么、范围收到哪里讲清楚。第二段进入架构和数据模型，这是答辩的核心。第三段是交互实现细节和质量门禁。
-->
