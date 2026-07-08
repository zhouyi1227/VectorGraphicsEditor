---
layout: default
transition: slide-left
---

# 项目概述

<div class="deck-rule"></div>

<div class="statement-band mb-5">
  C++20 / Qt 6 桌面矢量图形编辑器：画布里能创建、编辑、变换 7 种基础图形，文档保存为自定义 <code>.vgjson</code>，支持 PNG 导出、中英文切换和明暗主题。
</div>

<div class="metric-strip mb-5">
  <div v-click class="metric">
    <div class="metric-value">44</div>
    <div class="metric-label">源文件</div>
    <div class="metric-note"><code>*.cpp + *.h</code></div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">4431</div>
    <div class="metric-label">代码行</div>
    <div class="metric-note">不含 tests</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">5 / 40</div>
    <div class="metric-label">测试模块 / 用例</div>
    <div class="metric-note">Qt Test + CTest</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">7</div>
    <div class="metric-label">基础图形</div>
    <div class="metric-note">点/线/折线/多边形/圆/椭圆/矩形</div>
  </div>
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">能力栈</div>
    <div class="thin-divider"></div>
    <div class="support-grid">
      <div v-click class="support-row">
        <div class="support-key">能力</div>
        <div class="support-copy">绘制、选择、属性编辑、框选、缩放、复制粘贴、文档保存、PNG 导出。</div>
      </div>
      <div v-click class="support-row">
        <div class="support-key">技术栈</div>
        <div class="support-copy">C++20 / Qt 6 Widgets+Graphics View / CMake Presets / Ninja / Qt Test</div>
      </div>
      <div v-click class="support-row">
        <div class="support-key">跨平台</div>
        <div class="support-copy">Windows (MSYS2 UCRT64)、Linux、macOS 三套 preset</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">知识点</div>
      <div class="rail-title">OOP 概念集中服务于同一项目</div>
      <div class="rail-copy">继承、多态、抽象类、静态成员、文件 I/O、单元测试——全部落到具体代码里，没有分散到小例子中。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">讲解重点</div>
      <div class="rail-title">分层、边界、几何、质量门禁</div>
      <div class="rail-copy">四层架构、ShapeData 边界对象、几何中间表示、测试+格式检查质量门禁。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页先把量级摆出来：44 个源文件、4431 行 C++，5 个测试模块、40 个测试用例，7 种基础图形。
-->
