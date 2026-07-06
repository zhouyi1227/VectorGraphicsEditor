---
layout: default
transition: fade
hideInToc: true
---

# 目录

<div class="deck-rule"></div>

<div class="deck-lead">
  讲述路线只保留一条主线：先说明项目要解决什么问题，再展示系统如何组织，最后用关键实现与质量证据回答“为什么这样设计”。
</div>

<div class="split-2">
  <div class="deck-stage">
    <Toc columns="2" minDepth="1" maxDepth="1" />
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">FOCUS 01</div>
      <div class="rail-title">系统先于代码</div>
      <div class="rail-copy">先建立功能闭环和架构边界，再进入类、接口和几何逻辑。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">FOCUS 02</div>
      <div class="rail-title">实现先于术语</div>
      <div class="rail-copy">每个知识点都对应到真实文件、真实交互或真实测试，而不是空讲定义。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">FOCUS 03</div>
      <div class="rail-title">证据先于结论</div>
      <div class="rail-copy">最后会用文件格式、测试、构建链路和现场操作证明系统稳定可验证。</div>
    </div>
  </div>
</div>

<!--
目录页提醒老师：我后面会先从项目目标和功能切入，再进入核心代码与课程知识点。这样后续每一页不会像零散贴代码，而是沿着一条主线推进。
-->
