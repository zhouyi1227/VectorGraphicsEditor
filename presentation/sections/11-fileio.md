---
layout: default
transition: slide-left
---

# 事件分发流程

<style>
.deck-lead { margin-bottom: 0.4rem; font-size: 0.82rem; line-height: 1.4; }
.event-flow { display: flex; align-items: center; gap: 0.4rem; padding: 0.5rem 0.4rem; flex-wrap: nowrap; justify-content: center; }
.event-node { background: var(--deck-blue-soft); border: 1px solid var(--deck-blue); border-radius: 0.4rem; padding: 0.3rem 0.55rem; font-size: 0.74rem; color: #0a3e63; white-space: nowrap; }
.event-router { background: #fff; border: 1.5px solid var(--deck-blue); color: #0a3e63; font-weight: 600; }
.event-arrow { color: var(--deck-blue); font-size: 0.9rem; flex: 0 0 auto; }
.event-branches { display: grid; grid-template-rows: repeat(4, auto); gap: 0.2rem; padding: 0.1rem 0.4rem; border-left: 1px dashed var(--deck-line); }
.event-branch { font-size: 0.72rem; color: var(--deck-body); }
.event-branch b { color: #0a3e63; font-weight: 600; }
.event-takeaways { display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 0.6rem; margin-top: 0.5rem; }
.event-take { padding: 0.45rem 0.7rem; border-left: 2px solid var(--deck-blue); background: rgba(234,246,253,0.4); border-radius: 0 0.3rem 0.3rem 0; }
.event-take-h { font-size: 0.7rem; font-weight: 700; color: var(--deck-blue); letter-spacing: 0.05em; }
.event-take-b { font-size: 0.72rem; color: #0b2235; line-height: 1.4; margin-top: 0.15rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  同一时刻，哪个会话拥有控制权。输入一旦进入某个会话，后续事件不会再误流向别的路径。
</div>

<div class="event-flow">
  <div class="event-node">鼠标 / 键盘事件</div>
  <div class="event-arrow">→</div>
  <div class="event-node event-router">CanvasViewInput 路由</div>
  <div class="event-arrow">→</div>
  <div class="event-branches">
    <div class="event-branch"><b>手柄命中</b> → beginTransformSession</div>
    <div class="event-branch"><b>选中图形</b> → updateSelectionDrag</div>
    <div class="event-branch"><b>当前工具</b> → Strategy begin/update/finish</div>
    <div class="event-branch"><b>键盘命令</b> → Enter / Esc / Delete / Ctrl+C/V</div>
  </div>
</div>

<div class="event-takeaways">
  <div class="event-take">
    <div class="event-take-h">路由</div>
    <div class="event-take-b"><code>CanvasViewInput.cpp</code> 识别模式并决定流向，几何下放到策略和 <code>CanvasGeometry</code>。</div>
  </div>
  <div class="event-take">
    <div class="event-take-h">优先级</div>
    <div class="event-take-b">手柄 > 普通选中。拖缩放柄时不会误触发 item selection。</div>
  </div>
  <div class="event-take">
    <div class="event-take-h">互斥</div>
    <div class="event-take-b">所有会话互斥，事件只会流向一个明确入口。</div>
  </div>
</div>

<!--
各位老师，这一页我讲输入状态机的互斥性。关键是：所有会话是互斥的，事件只会流向一个明确入口。比如变换会话 begin 之后，mouseMove 不会再进入普通拖拽创建逻辑，这就是为什么拖缩放柄的时候不会同时创建出新的图形。具体的优先级是手柄 > 普通选中 > 当前工具。CanvasViewInput.cpp 负责识别当前模式并决定事件流向，几何计算被下放到策略和 CanvasGeometry 这两个独立的单元，互不污染。键盘事件负责结束、取消、删除、复制粘贴，是 mouse 之外的另一条闭环。
-->
