---
layout: default
transition: slide-left
---

# 项目概述

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="grid grid-cols-3 gap-4" style="margin-bottom:2rem;">

<div v-click class="card">
<div class="num">49</div>
<div class="lbl">源文件</div>
<div class="sml">26 .cpp + 23 .h</div>
</div>

<div v-click class="card">
<div class="num">11,014</div>
<div class="lbl">总代码行数</div>
<div class="sml">含测试 ~2000 行</div>
</div>

<div v-click class="card">
<div class="num">40</div>
<div class="lbl">测试用例</div>
<div class="sml">5 测试模块</div>
</div>

</div>

<v-clicks>

<div class="row">
<span class="dim">技术栈</span>
<span>C++20 · Qt 6.8 (Core/Gui/Widgets) · CMake ≥ 3.24 · Ninja</span>
</div>

<div class="row">
<span class="dim">架构</span>
<span>core → graphics → canvas → ui，strict 单向依赖</span>
</div>

<div class="row">
<span class="dim">工具链</span>
<span>clang-format · clang-tidy (bugprone/analyzer/modernize) · Qt Test + CTest</span>
</div>

<div class="row">
<span class="dim">跨平台</span>
<span>6 CMake 预设: Windows UCRT64 / Linux / macOS，各含 Debug/Release</span>
</div>

</v-clicks>

<style>
.card {
  border: 1px solid #e8e8e8;
  border-radius: 6px;
  padding: 1.2rem;
  text-align: center;
  background: #fafafa;
}
.card .num {
  font-size: 2rem;
  font-weight: 700;
  color: #2d7ff9;
}
.card .lbl {
  font-size: 0.85rem;
  color: #333;
  margin-top: 0.2rem;
}
.card .sml {
  font-size: 0.7rem;
  color: #999;
  margin-top: 0.15rem;
}
.row {
  display: flex;
  gap: 1.5rem;
  padding: 0.6rem 0;
  border-bottom: 1px solid #f0f0f0;
  font-size: 0.9rem;
}
.row .dim {
  color: #999;
  min-width: 5rem;
  font-weight: 500;
}
</style>

<!--
项目概况：49个源文件约11000行代码，40个测试用例覆盖核心逻辑。C++20标准，Qt6框架，CMake构建系统。四层严格单向依赖，核心层不依赖Qt Widgets。工具链配置了clang-format和clang-tidy保证代码质量。跨平台支持Windows/Linux/macOS三平台各两种构建配置。
-->
