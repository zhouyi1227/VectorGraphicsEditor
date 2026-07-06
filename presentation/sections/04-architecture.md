---
layout: default
transition: slide-left
---

# 分层架构

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="text-sm dim" style="margin-bottom:1.5rem;">core → graphics → canvas → ui，不可逆的单向依赖</div>

<div class="grid" style="display:grid;grid-template-columns:repeat(4,1fr);gap:0.75rem;margin-bottom:1.5rem;">

<div class="layer-box" style="background:#f8f8f8;">
<div class="layer-title" style="color:#666;">UI</div>
<div class="layer-items">
<div>MainWindow</div>
<div>PropertyPanel</div>
<div>TutorialDialog</div>
<div class="dim" style="font-size:0.75rem;">+ ThemeUtils</div>
</div>
</div>

<div class="layer-box">
<div class="layer-title" style="color:#666;">Canvas</div>
<div class="layer-items">
<div>CanvasView</div>
<div>ICreationStrategy</div>
<div>DragCreationStrategy</div>
<div>PathCreationStrategy</div>
<div class="dim" style="font-size:0.75rem;">+ MultiShapeSession</div>
</div>
</div>

<div class="layer-box">
<div class="layer-title" style="color:#666;">Graphics</div>
<div class="layer-items">
<div>ShapeItem</div>
<div>ShapeFactory</div>
</div>
</div>

<div class="layer-box">
<div class="layer-title" style="color:#666;">Core</div>
<div class="layer-items">
<div>ShapeData</div>
<div>SelectionFrame</div>
<div>FileManager</div>
<div class="dim" style="font-size:0.75rem;">+ I18n / Geometry</div>
</div>
</div>

</div>

<div class="flow-line">
<span><strong>core</strong> — 纯数据，零 Qt Widgets 依赖</span>
<span style="color:#2d7ff9;">→</span>
<span><strong>graphics</strong> — QGraphicsObject 图谱</span>
<span style="color:#2d7ff9;">→</span>
<span><strong>canvas</strong> — QGraphicsView + 策略</span>
<span style="color:#2d7ff9;">→</span>
<span><strong>ui</strong> — QMainWindow + Dock</span>
</div>

<v-click>

<div style="margin-top:1rem;padding:0.8rem 1rem;background:#fafafa;border:1px solid #eee;border-radius:4px;font-size:0.85rem;">
<span style="color:#2d7ff9;font-weight:700;">设计意图</span> — core 层编译为独立静态库 <code>svg_editor_core</code>，只依赖 Qt6::Core 和 Qt6::Gui。修改 ui 层无需重新编译 core 层。core 层的逻辑可在无 Qt Widgets 环境下独立测试。
</div>

</v-click>

<style>
.layer-box {
  border: 1px solid #e8e8e8;
  border-radius: 6px;
  padding: 0.8rem 1rem;
}
.layer-title {
  font-size: 0.7rem;
  font-weight: 600;
  text-transform: uppercase;
  letter-spacing: 0.1em;
  margin-bottom: 0.6rem;
}
.layer-items {
  font-size: 0.85rem;
  line-height: 1.7;
}
.flow-line {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 0.5rem;
  font-size: 0.8rem;
  color: #666;
  background: #fafafa;
  border-radius: 4px;
  padding: 0.6rem 1rem;
}
</style>

<!--
四层架构的设计理念是严格的单向依赖，箭头方向不可逆。core层编译为独立静态库svg_editor_core，只依赖Qt6::Core和Qt6::Gui。这样设计的好处是：修改UI层不会波及下面三层；core层的逻辑可以在无Qt Widgets环境下独立测试；如果要切换到不同的UI框架只需要替换最上层。
-->
