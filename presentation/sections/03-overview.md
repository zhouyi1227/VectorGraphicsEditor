---
layout: default
transition: slide-left
---

# 项目概述

<div class="deck-rule"></div>

<div class="statement-band mb-6">
  这个项目不是单一算法作业，而是一个完整的桌面矢量图形编辑器：既能在画布中创建与编辑图形，也能把结果稳定保存、重新加载并导出。
</div>

<div class="metric-strip mb-6">
  <div v-click class="metric">
    <div class="metric-value">44</div>
    <div class="metric-label">源码文件</div>
    <div class="metric-note"><code>VectorGraphicsEditor/*.cpp + *.h</code></div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">4431</div>
    <div class="metric-label">源码行数</div>
    <div class="metric-note">不含 <code>tests</code> 目录</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">5 / 40</div>
    <div class="metric-label">测试模块 / 测试函数</div>
    <div class="metric-note">Qt Test + CTest</div>
  </div>
  <div v-click class="metric">
    <div class="metric-value">7</div>
    <div class="metric-label">基础图形</div>
    <div class="metric-note">点、线、面、圆形族</div>
  </div>
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="support-grid">
      <div v-click class="support-row">
        <div class="support-key">项目定位</div>
        <div class="support-copy">覆盖绘制、选择、编辑、文档保存与 PNG 导出的完整闭环。</div>
      </div>
      <div v-click class="support-row">
        <div class="support-key">技术栈</div>
        <div class="support-copy">C++20、Qt 6 Widgets / Graphics View、CMake Presets、Ninja。</div>
      </div>
      <div v-click class="support-row">
        <div class="support-key">输出能力</div>
        <div class="support-copy">支持自定义 <code>.vgjson</code>、运行时中英文切换、系统 / 明亮 / 深色主题。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">课程价值</div>
      <div class="rail-title">知识点落到系统里</div>
      <div class="rail-copy">继承、多态、抽象类、静态成员、文件 I/O 和测试，不是分散小例子，而是集中服务同一个项目目标。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">讲解重点</div>
      <div class="rail-title">为什么它能长期保持一致</div>
      <div class="rail-copy">后面的重点会放在分层、边界对象、事件路由、几何约束和质量门禁，而不是只罗列功能按钮。</div>
    </div>
  </div>
</div>

<!--
这一页先建立量级感：项目不是 demo 级别，而是有明确模块边界、文件格式和测试体系的课程实践。这里的数字都来自当前仓库状态，后面再展开它们分别意味着什么。
-->
