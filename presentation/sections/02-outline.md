---
layout: default
transition: fade
hideInToc: true
---

# 目录

<style>
.split-2 { grid-template-columns: 1fr 1.05fr; gap: 1rem; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.5rem; }
.rail-item { padding-left: 0.7rem; }
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
.deck-stage { padding: 0.6rem 0.85rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  整场答辩走一条主线：先讲项目目标与功能边界，再讲架构与核心数据，最后用交互实现、测试、构建和现场演示回答「稳不稳、能不能跑」。
</div>

<div class="split-2">
  <div class="deck-stage">
    <Toc columns="2" minDepth="1" maxDepth="1" />
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">第 1 段</div>
      <div class="rail-title">项目目标与功能</div>
      <div class="rail-copy">第 3–5 页：项目概述、需求与目标、功能总览。说明系统能做什么、范围怎么收敛。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">第 2 段</div>
      <div class="rail-title">架构与核心数据</div>
      <div class="rail-copy">第 6–10 页：四层架构、ShapeData、继承体系、策略模式、依赖注入。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">第 3 段</div>
      <div class="rail-title">交互、实现、质量、现场</div>
      <div class="rail-copy">第 11–20 页：事件分发、绘制、I/O、选中变换、国际化、测试、构建、取舍、演示、结束。</div>
    </div>
  </div>
</div>

<!--
各位老师，我把内容切成四段。第一段先把项目是什么、目标是什么、范围收到哪里讲清楚，避免上来就贴代码。第二段进入架构和数据模型，这是答辩的核心，老师们最可能在这一段追问。第三段是交互和实现细节：事件怎么路由、图形怎么画、文件怎么存。第四段是质量门禁和现场演示：测试、构建、设计取舍，最后我用五步操作把整个系统跑一遍给老师看。
-->
