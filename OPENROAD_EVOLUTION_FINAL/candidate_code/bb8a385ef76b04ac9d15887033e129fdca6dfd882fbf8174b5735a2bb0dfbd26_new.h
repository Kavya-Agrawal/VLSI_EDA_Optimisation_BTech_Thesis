// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18944097;
  double density_weight = 0.43198320;
  double prefix_weight = 0.00824544;
  double neighborhood_weight = 0.31402716;
  double late_weight = 0.09649027;
  double critical_weight = 0.00727687;
  unsigned budget = 20;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
