---
layout: default
transition: slide-left
---

# 关键设计取舍 / 难点解决

<style>
.statement-band { font-size: 0.98rem; line-height: 1.45; margin-bottom: 0.8rem; }
.rail-copy { font-size: 0.8rem; line-height: 1.45; }
.rail-title { font-size: 0.9rem; }
.rail-list { gap: 0.5rem; }
.rail-item { padding-left: 0.7rem; }
</style>

<div class="deck-rule"></div>

<div class="statement-band mb-6">
  我在三个地方做了主动取舍：数据 / 视图分离、属性面板防重入、几何与文件契约保守收敛。每条都有具体的失败场景作为出发点。
</div>

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">取舍 1</div>
    <div class="rail-title">数据与视图分离</div>
    <div class="rail-copy"><code>CanvasView</code> 不直接读写 <code>ShapeItem</code> 内部状态，而是通过 <code>ShapeData</code> 与工厂 / setter 交互，序列化和复制逻辑因此保持稳定。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">取舍 2</div>
    <div class="rail-title">属性面板防重入</div>
    <div class="rail-copy"><code>m_updatingWidgets</code> 标志位阻断「程序更新控件 → valueChanged → 再次 emit」的死循环——这是界面稳定性的关键保护。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">取舍 3</div>
    <div class="rail-title">几何与文件契约保守收敛</div>
    <div class="rail-copy">缩放抽成 <code>SelectionFrame + CanvasGeometry</code>，文件固定 <code>version 2</code> 并拒绝旋转 transform，避免交互与 I/O 语义同时失控。</div>
  </div>
</div>

<!--
各位老师，这一页我讲三个我主动做的设计取舍，每条都对应一个具体的失败场景。第一条是数据与视图分离：早期我尝试过让 CanvasView 直接读写 ShapeItem 内部字段，结果每次 ShapeItem 内部状态调整都要改一堆 getter / setter。改成只通过 ShapeData 交互之后，序列化、复制粘贴、撤销/重做——如果将来要做——都只需要在 ShapeData 这一层处理。第二条是属性面板防重入：用户改控件会触发 valueChanged，valueChanged 写回 ShapeData，ShapeData 又触发 shapeChanged，shapeChanged 又通知属性面板更新——不阻断就是死循环。m_updatingWidgets 这个 bool 是界面层和模型层之间的握手协议。第三条是几何和文件契约保守收敛：SelectionFrame 解决朝向矩形问题，version 2 锁定文件格式，旋转 transform 明确拒绝——拒绝的理由在设计文档里写清楚了。
-->
