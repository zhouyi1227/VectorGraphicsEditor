---
layout: default
transition: slide-left
---

# 项目概述

<style>
.statement-band { font-size: 0.98rem; line-height: 1.45; margin-bottom: 0.8rem; }
.metric-strip { gap: 0.5rem; margin-bottom: 0.7rem !important; }
.metric-value { font-size: 1.7rem; }
.metric { padding-top: 0.5rem; }
.metric-label { font-size: 0.78rem; }
.metric-note { font-size: 0.66rem; }
.split-even { gap: 0.8rem; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.45rem; }
.rail-item { padding-left: 0.7rem; }
.support-grid { gap: 0.4rem; }
.support-row { padding-bottom: 0.4rem; gap: 0.7rem; grid-template-columns: 7rem 1fr; }
.support-key { font-size: 0.74rem; }
.support-copy { font-size: 0.8rem; line-height: 1.45; }
.deck-stage { padding: 0.65rem 0.9rem; }
</style>

<div class="deck-rule"></div>

<div class="statement-band mb-6">
  这是一个 C++20 / Qt 6 桌面矢量图形编辑器：画布里能创建、编辑、复制、变换 7 种基础图形，文档保存为自定义 <code>.vgjson</code>，支持 PNG 导出、中英文切换和明暗主题。
</div>

<div class="metric-strip mb-6">
  <div v-click class="metric">
    <div class="metric-value">44</div>
    <div class="metric-label">源文件</div>
    <div class="metric-note"><code>VectorGraphicsEditor/*.cpp + *.h</code></div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">4431</div>
    <div class="metric-label">代码行</div>
    <div class="metric-note">不含 <code>tests</code></div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">5 / 40</div>
    <div class="metric-label">测试模块 / 用例</div>
    <div class="metric-note">Qt Test + CTest</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">7</div>
    <div class="metric-label">基础图形</div>
    <div class="metric-note">点 / 线 / 折线 / 多边形 / 圆 / 椭圆 / 矩形</div>
  </div>
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="support-grid">
      <div v-click class="support-row">
        <div class="support-key">能力</div>
        <div class="support-copy">绘制、选择、属性编辑、橡皮筋框选、四角缩放、复制粘贴、文档保存、PNG 导出。</div>
      </div>
      <div v-click class="support-row">
        <div class="support-key">栈</div>
        <div class="support-copy">C++20、Qt 6 Widgets / Graphics View、CMake Presets v6、Ninja、Qt Test。</div>
      </div>
      <div v-click class="support-row">
        <div class="support-key">跨平台</div>
        <div class="support-copy">Windows（MSYS2 UCRT64）、Linux、macOS 各有对应 build / test preset。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">知识点分布</div>
      <div class="rail-title">OOP 概念落到代码里</div>
      <div class="rail-copy">继承（ShapeItem / 策略类）、多态（ICreationStrategy）、抽象类（策略基类）、静态成员、文件 I/O、单元测试——这些概念集中服务同一个项目目标，没有分散到小例子里。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">讲解重点</div>
      <div class="rail-title">分层、边界、几何、质量门禁</div>
      <div class="rail-copy">重点会放在四层架构、ShapeData 这个跨层边界对象、几何中间表示，以及测试 + 格式检查这套质量门禁。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页我先把量级摆出来：44 个源文件、4431 行 C++，4 个测试模块、40 个测试用例。7 种基础图形点、线、折线、多边形、圆、椭圆、矩形。栈是 C++20 + Qt 6 Graphics View + CMake Presets。跨平台走的是 Windows（MSYS2 UCRT64）、Linux、macOS 三套 preset。接下来的安排是：先讲项目目标与功能边界，再讲四层架构和核心数据模型，再用独立页面分别讲策略模式、依赖注入、事件分发，最后用测试、构建脚本和现场演示回答「稳不稳、跑不跑得动」。
-->
