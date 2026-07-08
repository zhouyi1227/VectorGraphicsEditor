---
layout: default
transition: slide-left
---

# 事件分发流程

<div class="deck-rule"></div>

<div class="deck-lead">
  同一时刻，哪个会话拥有控制权。输入一旦进入某个会话，后续事件不再误流向别的路径。
</div>

<div class="event-flow">
  <div class="event-node">鼠标 / 键盘事件</div>
  <div class="event-arrow">→</div>
  <div class="event-node event-router">CanvasViewInput 路由</div>
  <div class="event-arrow">→</div>
  <div class="event-branches">
    <div class="event-branch"><b>手柄命中</b> → beginTransformSession</div>
    <div class="event-branch"><b>选中图形</b> → updateSelectionDrag</div>
    <div class="event-branch"><b>当前工具</b> → Strategy</div>
    <div class="event-branch"><b>键盘命令</b> → Enter / Esc / Delete / Ctrl+C/V</div>
  </div>
</div>

<div class="event-takeaways">
  <div class="event-take">
    <div class="event-take-h">路由</div>
    <div class="event-take-b"><code>CanvasViewInput.cpp</code> 识别模式决定流向，几何下放到 <code>CanvasGeometry</code>。</div>
  </div>
  <div class="event-take">
    <div class="event-take-h">优先级</div>
    <div class="event-take-b">手柄 > 普通选中。拖缩放柄时不会误触发 item selection。</div>
  </div>
  <div class="event-take">
    <div class="event-take-h">互斥</div>
    <div class="event-take-b">所有会话互斥，事件只流向一个明确入口。</div>
  </div>
</div>

<!--
各位老师，这一页讲输入状态机的互斥性。关键是所有会话互斥，事件只流向一个明确入口。优先级是手柄 > 普通选中 > 当前工具。CanvasViewInput.cpp 负责识别模式并决定事件流向。
-->
