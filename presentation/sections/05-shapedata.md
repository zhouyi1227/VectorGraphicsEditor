---
layout: default
transition: slide-left
---

# 功能总览

<div class="deck-rule"></div>

<div class="deck-lead">
  从用户视角看，这个系统的能力可以概括为一条闭环：选工具、在画布中创建图形、实时修改样式与几何、批量变换，再把文档可靠地保存下来。
</div>

<div class="process-row mb-6">
  <div v-click class="process-step">
    <div class="process-no">STEP 01</div>
    <div class="process-title">选择工具</div>
    <div class="process-copy">点、线、折线、多边形、圆、椭圆、矩形。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 02</div>
    <div class="process-title">创建图形</div>
    <div class="process-copy">单击、拖拽或逐点累加，过程中持续显示 preview。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 03</div>
    <div class="process-title">编辑属性</div>
    <div class="process-copy">修改描边宽度、线型、填充色与几何参数。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 04</div>
    <div class="process-title">多选与变换</div>
    <div class="process-copy">支持橡皮筋框选、平移、四角缩放与比例约束。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 05</div>
    <div class="process-title">保存与导出</div>
    <div class="process-copy">使用 <code>.vgjson</code> 持久化，并可导出 PNG。</div>
  </div>
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">创建链路</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title"><code>Point</code></div>
        <div class="rail-copy">单击即生成，适合作为最轻量的离散图元。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>Line / Circle / Ellipse / Rectangle</code></div>
        <div class="rail-copy">按下、拖拽、释放完成，适合用对角线或包围框定义几何。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>Polyline / Polygon</code></div>
        <div class="rail-copy">逐点累加，<code>Enter</code> 或双击结束，支持更自由的路径描述。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">编辑能力</div>
      <div class="rail-title">实时反馈</div>
      <div class="rail-copy">属性面板与选择状态联动，复制、粘贴、删除和拖拽都在画布中即时可见。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">产品细节</div>
      <div class="rail-title">中英文与主题切换</div>
      <div class="rail-copy">语言和外观不是附加装饰，而是完整桌面应用体验的一部分。</div>
    </div>
  </div>
</div>

<!--
这一页从用户视角讲功能，不急着进代码。答辩时可以把“创建链路”和“编辑链路”对应到后面策略模式、事件分发和几何变换三页，让老师先知道系统究竟能做什么。
-->
