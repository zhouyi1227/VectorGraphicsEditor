---
layout: default
transition: slide-left
---

<div class="relative h-full flex flex-col justify-center" style="padding: 3rem 4rem;">

<!-- decorative circles -->
<div class="absolute" style="top:-60px;right:-40px;width:200px;height:200px;border:1px solid #e0e0e0;border-radius:50%"></div>
<div class="absolute" style="bottom:-40px;left:-30px;width:140px;height:140px;border:1px solid #eee;border-radius:50%"></div>
<div class="absolute" style="top:40%;right:60px;width:6px;height:6px;border-radius:50%;background:#2d7ff9"></div>
<div class="absolute" style="bottom:30%;left:80px;width:4px;height:4px;border-radius:50%;background:#2d7ff9"></div>

<div class="relative" style="z-index:1;max-width:80%">

<div class="text-xs tracking-widest" style="color:#999;margin-bottom:1.5rem;letter-spacing:0.15em;">面向对象程序设计 · 课程设计</div>

<h1 style="font-size:2.8rem;font-weight:700;line-height:1.2;margin:0 0 0.3rem 0;letter-spacing:-0.02em;">SVG 矢量图形<span style="color:#2d7ff9">绘制系统</span></h1>

<div style="height:3px;width:48px;background:#2d7ff9;margin:1.5rem 0;"></div>

<div class="flex flex-wrap gap-2" style="margin-bottom:2rem;">
<span class="tag">C++20</span>
<span class="tag">Qt6</span>
<span class="tag">CMake / Ninja</span>
<span class="tag">49 源文件</span>
</div>

<div class="text-sm" style="color:#999;">
<span>2025 · github.com/anomalyco/SVG_Editor</span>
</div>

</div>

</div>

<style>
.tag {
  display: inline-block;
  padding: 0.2rem 0.8rem;
  font-size: 0.75rem;
  color: #666;
  background: #f5f5f5;
  border-radius: 3px;
}
</style>

<!--
各位老师好。今天汇报的是基于C++20和Qt6开发的SVG矢量图形绘制系统，共49个源文件约11000行代码。实现了7种基本图形的创建、编辑、选中变换、文件序列化和PNG导出等功能。项目采用四层单向依赖架构，使用了策略模式、工厂模式等设计模式，配有多语言界面和深色/浅色主题。
-->
