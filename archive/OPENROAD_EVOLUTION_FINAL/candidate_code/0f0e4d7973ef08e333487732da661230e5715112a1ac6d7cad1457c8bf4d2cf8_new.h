// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60275066;
  double density_weight = 0.26429126;
  double prefix_weight = 0.06937008;
  double neighborhood_weight = 0.38794156;
  double late_weight = 0.21290891;
  double critical_weight = 0.00724870;
  unsigned budget = 22;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
