---
layout: default
transition: slide-left
---

# 功能总览

<div class="deck-rule"></div>

<div class="deck-lead">
  从用户视角看，系统能力可以拆成五步。这五步走完，编辑链路就闭合了。
</div>

<div class="process-row mb-5">
  <div v-click class="process-step">
    <div class="process-no">STEP 01</div>
    <div class="process-title">选工具</div>
    <div class="process-copy">点、线、折线、多边形、圆、椭圆、矩形。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 02</div>
    <div class="process-title">创建图形</div>
    <div class="process-copy">单击、拖拽、逐点累加，实时 preview。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 03</div>
    <div class="process-title">改属性</div>
    <div class="process-copy">描边、线型、填充、几何参数实时联动。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 04</div>
    <div class="process-title">多选 + 变换</div>
    <div class="process-copy">框选、平移、四角缩放，Shift 等比。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 05</div>
    <div class="process-title">保存 + 导出</div>
    <div class="process-copy"><code>.vgjson</code> 持久化，PNG 导出。</div>
  </div>
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">创建链路</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title"><code>Point</code></div>
        <div class="rail-copy">单击即生成，离散图元。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>Line / Circle / Ellipse / Rectangle</code></div>
        <div class="rail-copy">按下→拖拽→释放，由对角线定义。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>Polyline / Polygon</code></div>
        <div class="rail-copy">逐点累加，Enter 或双击结束。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">编辑</div>
      <div class="rail-title">实时反馈</div>
      <div class="rail-copy">属性面板与选中状态联动，复制粘贴即时可见。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">桌面体验</div>
      <div class="rail-title">中英文 + 主题</div>
      <div class="rail-copy">语言和外观可切换，重启后保留。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页把系统能力清单说清楚。五步是：选工具、创建、改属性、多选变换、保存导出。创建链路分两条：拖拽创建和路径创建，对应后面讲的 DragCreationStrategy 和 PathCreationStrategy。
-->
